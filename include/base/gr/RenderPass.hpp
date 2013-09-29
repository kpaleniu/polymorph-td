#pragma once

#include "gr/types.hpp"
#include "gr/Texture.hpp"
#include "gr/Shader.hpp"
#include "gr/TextureManager.hpp"
#include "gr/IndexBuffer.hpp"

#include <NonCopyable.hpp>

#include <vector>


// TODO Needs refactoring

namespace polymorph { namespace gr {

class RenderPass : NonCopyable
{
public:
	RenderPass( Primitive shape,
				TextureManager::Handle texture,
				const Shader* shader );

	RenderPass(RenderPass&& other);

	std::vector<index_t>			indices;
	const TextureManager::Handle	texture;
	const Shader*					shader;
	const Primitive					shape;

	IndexBuffer indexBuffer;

	void buildIndices();

};

} }