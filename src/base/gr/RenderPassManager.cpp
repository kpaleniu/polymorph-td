#include "gr/RenderPassManager.hpp"

#include <Scoped.hpp>
#include <Assert.hpp>

namespace gr {

// VertexRenderContext

RenderPassManager::VertexRenderContext::VertexRenderContext(VertexFormat format)
:	source(format), buffer(format, BufferUsage::DYNAMIC)
{
}

RenderPassManager::VertexRenderContext::
	VertexRenderContext(VertexRenderContext&& other)
:	source(std::move(other.source)),
	buffer(std::move(other.buffer))
{
}

void RenderPassManager::VertexRenderContext::buildVertexBuffer()
{
	auto format = getVertexFormatData(source.format);

	ASSERT(source.vertices.size() % format.vertDim == 0,
		   "Vertex in incorrect format");

	std::size_t newSize = source.vertices.size() / format.vertDim;

#ifdef _DEBUG
	if (format.colorDim > 0)
		ASSERT(source.colors.size() / format.colorDim == newSize,
			   "Color in incorrect format.");

	if (format.normalDim > 0)
		ASSERT(source.normals.size() / format.normalDim == newSize,
			   "Normals in incorrect format.");

	if (format.textDim > 0)
		ASSERT(source.texCoords.size() / format.textDim == newSize,
		"Texture coordinates in incorrect format.");
#endif

	std::size_t currentSize = buffer.getVertexCount();

	// TODO Only re-create when newSize is larger?
	if (newSize != currentSize)
		buffer = VertexBuffer(source.format, BufferUsage::DYNAMIC, newSize);

	if (newSize == 0)
		return;

	buffer.writeVertices(0, newSize, source.vertices.data());
	
	if (format.colorDim > 0)
		buffer.writeColors(0, newSize, source.colors.data());
	if (format.normalDim > 0)
		buffer.writeNormals(0, newSize, source.normals.data());
	if (format.textDim > 0)
		buffer.writeTextureCoords(0, newSize, source.normals.data());
}


// RenderPassManager

RenderPassManager::RenderPassManager()
:	_renderPasses(), 
	_vertexContexts()
{
}

RenderPassManager::RenderPassManager(RenderPassManager&& other)
:	_renderPasses(std::move(other._renderPasses)), 
	_vertexContexts(std::move(other._vertexContexts))
{
}

VertexWriter RenderPassManager::vertexWriter(VertexFormat format)
{
	VertexRenderContext* foundContext = nullptr;

	// Find or create render context:
	{
		auto it = _vertexContexts.find(format);

		if (it == _vertexContexts.end())
		{
			VertexRenderContext newRenderContext(format);

			auto rcIt = _vertexContexts.insert(
				std::make_pair(format, std::move(newRenderContext)));

			foundContext = &rcIt.first->second;
		}
		else
		{
			foundContext = &it->second;
		}
	}


	return VertexWriter(foundContext->source);
}

IndexWriter RenderPassManager::indexWriter(VertexFormat format,
										   Primitive shape,
										   TextureManager::TextureHandle tex,
										   const Shader* shader)
{
	auto beginEndPair = _renderPasses.equal_range(format);

	RenderPass* foundPass = nullptr;

	// Find or create render pass:
	{
		for (auto it = beginEndPair.first; it != beginEndPair.second; ++it)
		{
			RenderPass& pass = it->second;

			if (pass.shape == shape
				&& pass.texture == tex
				&& pass.shader == shader)
			{
				foundPass = &pass;
				break;
			}
		}

		if (foundPass == nullptr)
		{
			auto it = _renderPasses.insert(
				std::make_pair(format,
				RenderPass(shape, tex, shader)));
			foundPass = &it->second;
		}
	}

	return IndexWriter(foundPass->indices);
}

void RenderPassManager::render(const MapMatrix4x4_r& projection,
							   const MapMatrix4x4_r& worldInverseTransform)
{
	gl::matrixMode(GL_PROJECTION);
	gl::loadMatrix(projection.data());

	gl::matrixMode(GL_MODELVIEW);
	gl::loadMatrix(worldInverseTransform.data());

	for (auto& fmtContexPair : _vertexContexts)
	{
		const VertexFormat& format = fmtContexPair.first;
		VertexRenderContext& context = fmtContexPair.second;

		auto beginEndPair = _renderPasses.equal_range(format);

		context.buildVertexBuffer();
		context.source.clear();

		for (auto it = beginEndPair.first; it != beginEndPair.second; ++it)
		{
			RenderPass& pass = it->second;

			pass.buildIndices();
			pass.indices.clear();

			context.buffer.draw(pass.shape, pass.indexBuffer);
		}
	}
}

}
