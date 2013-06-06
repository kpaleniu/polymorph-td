


#ifndef TEX_LOADER_HPP
#define TEX_LOADER_HPP

#include "gr/Texture.hpp"
#include <resource/ResourceLoader.hpp>

namespace gr {

class TextureLoader : public resource::ResourceLoader<Texture>
{
public:
	typedef resource::ResourceLoader<Texture>::ResourceHandle TextureHandle;

	TextureLoader();

	TextureHandle addTexture(text::string_hash id, Texture&& texture);
	TextureHandle getTexture(text::string_hash id);
	TextureHandle getNullTexture();
};

}

#endif
