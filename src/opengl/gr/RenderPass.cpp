/**
 * @file Renderer_GL.cpp
 *
 */

#include "gr/RenderPass.hpp"
#include "gr/opengl.hpp"
#include "gr/Texture.hpp"

#include <Debug.hpp>

namespace gr {

RenderPass::RenderPass(VertexFormat format,
                       Primitive shape,
                       MaterialDesc materialDesc,
                       BufferDesc bufferDesc,
                       const TransformDesc& transformDesc)
:	_shape(shape),
 	_vertices(format, BufferUsage::DYNAMIC),
 	_indices(BufferUsage::DYNAMIC),
 	_vertexWriter(_vertices, _indices),
 	_materialDesc(materialDesc),
 	_bufferDesc(bufferDesc),
 	_transformDesc( {transformDesc.projection,
					 transformDesc.view,
					 transformDesc.model} ),
 	_invTransformDesc( {transformDesc.projection.inverse(),
						transformDesc.view.inverse(),
						transformDesc.model.inverse()} ),
 	_vertexSuppliers(),
 	_preRenderHook(),
 	_postRenderHook(),
 	_needUpdate(true)
{
}

RenderPass::RenderPass(RenderPass&& other)
:	_shape(other._shape),
 	_vertices(std::move(other._vertices)),
 	_indices(std::move(other._indices)),
 	_vertexWriter(_vertices, _indices),
 	_materialDesc(other._materialDesc),
 	_bufferDesc(other._bufferDesc),
 	_transformDesc( {other._transformDesc.projection,
					 other._transformDesc.view,
					 other._transformDesc.model}),
	_invTransformDesc( {other._transformDesc.projection.inverse(),
						other._transformDesc.view.inverse(),
						other._transformDesc.model.inverse()} ),
 	_vertexSuppliers(std::move(other._vertexSuppliers)),
 	_preRenderHook(other._preRenderHook),
 	_postRenderHook(other._postRenderHook),
 	_needUpdate(other._needUpdate)
{
}

RenderPass::VertexSupplierHandle RenderPass::addVertexSupplier(VertexSupplier& vertexSupplier)
{
	return VertexSupplierHandle(_vertexSuppliers.insert(_vertexSuppliers.end(), &vertexSupplier));
}

void RenderPass::removeVertexSupplier(VertexSupplierHandle handle)
{
	_vertexSuppliers.erase((vertex_supplier_iterator) handle);
}

void RenderPass::clearVertexSuppliers()
{
	_vertexSuppliers.clear();
}

void RenderPass::updateVertices()
{
	for (auto supplier : _vertexSuppliers)
		supplier->writeVertices(_vertexWriter);

	_vertexWriter.flush();

	_needUpdate = false;
}

void RenderPass::render()
{
	if (_needUpdate)
		updateVertices();

	if (_preRenderHook)
		_preRenderHook(*this);

	if ( _bufferDesc.clearFlags != enum_t(BufferFlag::NONE) )
		glClear( GLenum(_bufferDesc.clearFlags) );

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(_transformDesc.projection.data());

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(_transformDesc.view.data());
	glMultMatrixf(_transformDesc.model.data());

	if (_materialDesc.texture != nullptr)
	{
		gl::enable(GL_TEXTURE_2D);
		_materialDesc.texture->bind();
	}

	if (_materialDesc.shader != nullptr)
	{
		// TODO Implement
	}

	if ( !_vertices.isEmpty() )
		_vertices.draw(_shape, _indices);

	if (_materialDesc.texture != nullptr)
	{
		_materialDesc.texture->unbind();
		gl::disable(GL_TEXTURE_2D);
	}

	if (_postRenderHook)
		_postRenderHook(*this);

	_needUpdate = true;
}

void RenderPass::preRender(Hook hook)
{
	_preRenderHook = hook;
}

void RenderPass::postRender(Hook hook)
{
	_postRenderHook = hook;
}

ModelVector RenderPass::unProject(const ClipVector& clipVec) const
{
	Vector3_r v = _invTransformDesc.model
					* (_invTransformDesc.view
						* (_invTransformDesc.projection * static_cast<const Vector3_r&>(clipVec)));
	return ModelVector(v);
}

ClipVector RenderPass::project(const ModelVector& modelVec) const
{
	Vector3_r v = _transformDesc.projection
	                * (_transformDesc.view
	               	  * (_transformDesc.model * static_cast<const Vector3_r&>(modelVec)));

	return ClipVector(v);
}


void RenderPass::setProjection(const Projection& projection)
{
	_transformDesc.projection = projection;
	_invTransformDesc.projection = projection.inverse();
}

void RenderPass::setModelTransform(const Transform& modelTransform)
{
	_transformDesc.model = modelTransform;
	_invTransformDesc.model = modelTransform.inverse();
}

void RenderPass::setViewTransform(const Transform& viewTransform)
{
	_transformDesc.view = viewTransform;
	_invTransformDesc.view = viewTransform.inverse();
}

void RenderPass::setTexture(const Texture* tex)
{
	_materialDesc.texture = tex;
}

void RenderPass::setShader(const Shader* shader)
{
	_materialDesc.shader = shader;
}

}

