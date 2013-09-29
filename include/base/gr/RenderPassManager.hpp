#pragma once

#include "gr/RenderPass.hpp"
#include "gr/TextureManager.hpp"
#include "gr/VertexWriter.hpp"

#include <NonCopyable.hpp>

#include <map>

namespace polymorph { namespace gr {

/**
 * Render pass composition.
 */
class RenderPassManager : NonCopyable
{
public:
	RenderPassManager();
	RenderPassManager(RenderPassManager&& other);

	VertexWriter vertexWriter(VertexFormat format);

	IndexWriter  indexWriter(VertexFormat format,
							 Primitive shape,
							 TextureManager::Handle tex,
							 const Shader* shader);

	void render(const MapMatrix4x4_r& projection,
				const MapMatrix4x4_r& worldInverseTransform);

private:

	class VertexRenderContext : NonCopyable
	{
	public:
		VertexRenderContext(VertexFormat format);
		VertexRenderContext(VertexRenderContext&& other);

		// Writes source vectors to buffer.
		void buildVertexBuffer();

		VertexSource source;
		VertexBuffer buffer;
	};

	std::multimap<VertexFormat, RenderPass> _renderPasses;
	std::map<VertexFormat, VertexRenderContext> _vertexContexts;

};

} }