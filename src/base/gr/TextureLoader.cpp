#include "gr/TextureLoader.hpp"

namespace gr {

TextureLoader::TextureHandle TextureLoader::addTexture(text::string_hash id,
                                        Texture&& texture)
{
	return addProduct(id, std::move(texture));
}

TextureLoader::TextureHandle TextureLoader::getTexture(text::string_hash id)
{
	return getProduct(id);
}

TextureLoader::TextureHandle TextureLoader::getNullTexture()
{
	return TextureHandle();
}

}

