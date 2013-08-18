/**
 * @file Renderer_GL.cpp
 *
 */

#include "gr/RenderPass.hpp"
#include "gr/opengl.hpp"
#include "gr/Texture.hpp"

#include <Debug.hpp>

namespace gr {

RenderPass::RenderPass(Primitive shape_,
                       TextureManager::TextureHandle texture_,
					   const Shader* shader_)
:	shape(shape_),
 	indices(),
 	texture(texture_),
	shader(shader_),
	indexBuffer(BufferUsage::DYNAMIC)
{
}

RenderPass::RenderPass(RenderPass&& other)
:	shape(other.shape),
 	indices(std::move(other.indices)),
 	texture(other.texture),
	shader(other.shader),
	indexBuffer(std::move(other.indexBuffer))
{
}

void RenderPass::buildIndices()
{
	if (indexBuffer.getIndexCount() != indices.size())
		indexBuffer = IndexBuffer(BufferUsage::DYNAMIC, indices.size());

	indexBuffer.writeIndices(0, indices.size(), indices.data());
}

}

