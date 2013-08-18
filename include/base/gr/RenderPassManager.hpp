/**
 * @file RenderPassManager.hpp
 *
 */

#ifndef RENDERPASSMANAGER_HPP_
#define RENDERPASSMANAGER_HPP_

#include "gr/RenderPass.hpp"
#include "gr/TextureManager.hpp"
#include "gr/VertexWriter.hpp"

#include <NonCopyable.hpp>

#include <map>

namespace gr {

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
							 TextureManager::TextureHandle tex,
							 const Shader* shader);

	void render();

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

}


#endif /* RENDERPASSMANAGER_HPP_ */
