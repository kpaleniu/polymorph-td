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
                       const Texture* texture,
					   const Shader* shader)
:	_shape(shape),
 	_vertices(format, BufferUsage::DYNAMIC),
 	_indices(BufferUsage::DYNAMIC),
 	_vertexWriter(_vertices, _indices),
 	_texture(texture),
	_shader(shader)
{
}

RenderPass::RenderPass(RenderPass&& other)
:	_shape(other._shape),
 	_vertices(std::move(other._vertices)),
 	_indices(std::move(other._indices)),
 	_vertexWriter(_vertices, _indices),
 	_texture(other._texture),
	_shader(other._shader)
{
}

VertexWriter& RenderPass::vertexWriter()
{
	return _vertexWriter;
}

void RenderPass::flushVertices()
{
	_vertexWriter.flush();

	if ( _vertices.isEmpty() )
		return;

	if (_texture != nullptr)
	{
		gl::enable(GL_TEXTURE_2D);
		_texture->bind();
	}

	if (_shader != nullptr)
	{
		// TODO Implement
	}

	_vertices.draw(_shape, _indices);

	if (_texture != nullptr)
	{
		_texture->unbind();
		gl::disable(GL_TEXTURE_2D);
	}
}

}

