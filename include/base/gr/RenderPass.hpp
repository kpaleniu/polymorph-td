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
			    const Texture* texture,
				const Shader* shader );

	RenderPass(RenderPass&& other);

	void flushVertices();

	VertexWriter& vertexWriter();

	const Texture* texture() const	{ return _texture; }
	const Shader* shader() const	{ return _shader; }
	VertexFormat format() const		{ return _vertices.getVertexFormat(); }
	Primitive shape() const			{ return _shape; }

private:
	Primitive _shape;

	VertexBuffer _vertices;
	IndexBuffer _indices;

	VertexWriter _vertexWriter;

	const Texture* _texture;
	const Shader*  _shader;
};

}


#endif /* RENDERPASS_HPP_ */
