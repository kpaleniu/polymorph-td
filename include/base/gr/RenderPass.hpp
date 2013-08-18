/**
 * @file RenderPass.hpp
 *
 */

#ifndef RENDERPASS_HPP_
#define RENDERPASS_HPP_

#include "gr/types.hpp"
#include "gr/Texture.hpp"
#include "gr/Shader.hpp"
#include "gr/TextureManager.hpp"
#include "gr/IndexBuffer.hpp"

#include <NonCopyable.hpp>

#include <vector>


// TODO Needs refactoring

namespace gr {

class RenderPass : NonCopyable
{
public:
	RenderPass( Primitive shape,
				TextureManager::TextureHandle texture,
				const Shader* shader );

	RenderPass(RenderPass&& other);

	std::vector<index_t>				indices;
	const TextureManager::TextureHandle texture;
	const Shader*						shader;
	const Primitive						shape;

	IndexBuffer indexBuffer;

	void buildIndices();

};

}


#endif /* RENDERPASS_HPP_ */
