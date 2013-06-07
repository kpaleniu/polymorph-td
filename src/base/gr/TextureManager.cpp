#include "gr/TextureManager.hpp"

namespace gr {

TextureManager::TextureHandle TextureManager::addTexture(text::string_hash id,
                                        Texture&& texture)
{
	return addProduct(id, std::move(texture));
}

TextureManager::TextureHandle TextureManager::getTexture(text::string_hash id)
{
	return getProduct(id);
}

TextureManager::TextureHandle TextureManager::getNullTexture()
{
	return TextureHandle();
}

}

