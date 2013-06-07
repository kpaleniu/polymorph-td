/**
 * @file RenderPass.hpp
 *
 */

#ifndef RENDERPASS_HPP_
#define RENDERPASS_HPP_

#include "gr/types.hpp"
#include "gr/VertexBuffer.hpp"
#include "gr/IndexBuffer.hpp"
#include "gr/VertexWriter.hpp"
#include "gr/Texture.hpp"
#include "gr/Shader.hpp"
#include "gr/TextureManager.hpp"

#include <PrivateHandle.hpp>
#include <NonCopyable.hpp>

#include <functional>
#include <list>

namespace gr {

class RenderPass : NonCopyable
{
public:

	RenderPass( VertexFormat format,
	            Primitive shape,
				TextureManager::TextureHandle texture,
				const Shader* shader );

	RenderPass(RenderPass&& other);

	void flushVertices();

	VertexWriter& vertexWriter();

	TextureManager::TextureHandle texture() const	{ return _texture; }
	const Shader* shader() const					{ return _shader; }
	VertexFormat format() const						{ return _vertices.getVertexFormat(); }
	Primitive shape() const							{ return _shape; }

private:
	Primitive _shape;

	VertexBuffer _vertices;
	IndexBuffer _indices;

	VertexWriter _vertexWriter;

	TextureManager::TextureHandle _texture;
	const Shader*  _shader;
};

}


#endif /* RENDERPASS_HPP_ */
