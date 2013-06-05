#include "gr/RenderPassManager.hpp"

#include <Scoped.hpp>
#include <Assert.hpp>

namespace gr {

RenderPassManager::RenderPassManager()
:	_projectionPool(),
	_transformPool(),
	_currentProjectionIndex(RandomAccessTreeEntry<Projection>::NULL_PARENT_INDEX),
	_currentTransformIndex(RandomAccessTreeEntry<Transform>::NULL_PARENT_INDEX),
	_renderPasses()
{
}

RenderPassManager::RenderPassManager(RenderPassManager&& other)
:	_projectionPool( std::move(other._projectionPool) ),
	_transformPool( std::move(other._transformPool)) ,
	_currentProjectionIndex( other._currentProjectionIndex ),
	_currentTransformIndex( other._currentTransformIndex )
{
}

void RenderPassManager::pushProjection(const Projection& projection)
{
	RandomAccessTreeEntry<Projection> entry = {_currentProjectionIndex, projection};
	_projectionPool.push_back(entry);
	_currentProjectionIndex = _projectionPool.size() - 1;
}

void RenderPassManager::popProjection()
{
	ASSERT(_currentProjectionIndex != RandomAccessTreeEntry<Projection>::NULL_PARENT_INDEX,
		   "Projection stack underflow.");

	_currentProjectionIndex = _projectionPool[_currentProjectionIndex].parentIndex;
}


void RenderPassManager::pushTransform(const Transform& transform)
{
	RandomAccessTreeEntry<Transform> entry = {_currentTransformIndex, transform};
	_transformPool.push_back(entry);
	_currentTransformIndex = _transformPool.size() - 1;
}

void RenderPassManager::popTransform()
{
	ASSERT(_currentTransformIndex != RandomAccessTreeEntry<Transform>::NULL_PARENT_INDEX,
		   "Transform stack underflow.");

	_currentTransformIndex = _transformPool[_currentTransformIndex].parentIndex;
}

VertexWriter& RenderPassManager::vertexWriter(VertexFormat format,
											  Primitive shape,
											  const Texture* tex,
											  const Shader* shader)
{
	WorldState currentState = {_currentProjectionIndex, _currentTransformIndex};

	auto beginEndPair = _renderPasses.equal_range(currentState);


	// Try to find render pass that matches current state and formats...

	for (auto it = beginEndPair.first; it != beginEndPair.second; ++it)
	{
		RenderPass& pass = it->second;

		if (pass.format() == format
			&& pass.shape() == shape
			&& pass.texture() == tex
			&& pass.shader() == shader)
		{
			return pass.vertexWriter();
		}
	}


	// ... if not found, create it.

	auto it = _renderPasses.insert( std::make_pair(currentState, 
									RenderPass(format, shape, tex, shader)) );

	return it->second.vertexWriter();
}

void RenderPassManager::render()
{
	projection_index lastProj = RandomAccessTreeEntry<Projection>::NULL_PARENT_INDEX;
	transform_index lastTrans = RandomAccessTreeEntry<Transform>::NULL_PARENT_INDEX;

	gl::matrixMode(GL_PROJECTION);
	gl::loadIdentity();
	gl::matrixMode(GL_MODELVIEW);
	gl::loadIdentity();

	for (auto& statePassPair : _renderPasses)
	{
		auto& state = statePassPair.first;
		auto& renderPass = statePassPair.second;

		if (state.projection != lastProj)
		{
			gl::matrixMode(GL_PROJECTION);
			gl::loadMatrix(_projectionPool[state.projection].data.data());

			lastProj = state.projection;
		}
		
		if (state.transformation != lastTrans)
		{
			gl::matrixMode(GL_MODELVIEW);
			gl::loadMatrix(_transformPool[state.transformation].data.asAffineMatrix().data());

			lastTrans = state.transformation;
		}

		renderPass.flushVertices();
	}
}

void RenderPassManager::clear()
{
	_currentProjectionIndex = RandomAccessTreeEntry<Projection>::NULL_PARENT_INDEX;
	_currentTransformIndex = RandomAccessTreeEntry<Transform>::NULL_PARENT_INDEX;

	_projectionPool.clear();
	_transformPool.clear();
	_renderPasses.clear();
}

}
