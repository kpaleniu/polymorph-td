
#include "gr/SpriteSheet.hpp"

#include <Assert.hpp>

namespace gr {

namespace {

std::map<SpriteSheet::sprite_id_t, std::array<gr::real_t, 8>>
convertAreas(unsigned int imageW,
             unsigned int imageH,
             const std::map<SpriteSheet::sprite_id_t, Rect<unsigned int>>& spriteAreas)
{
	std::map<SpriteSheet::sprite_id_t, std::array<gr::real_t, 8>> rMap;

	const real_t imageW_r = real_t(imageW);
	const real_t imageH_r = real_t(imageH);

	for (const auto& pair : spriteAreas)
	{
		const Rect<unsigned int>& imageRect = pair.second;

		ASSERT(imageRect.getRight() <= imageW
		       && imageRect.getTop() <= imageH, "Bad image coordinate");

		rMap[pair.first] = std::array<gr::real_t, 8>
		{
			{
				real_t(imageRect.getLeft()) / imageW_r,  real_t(imageRect.getBottom()) / imageH_r,
				real_t(imageRect.getRight()) / imageW_r, real_t(imageRect.getBottom()) / imageH_r,
				real_t(imageRect.getRight()) / imageW_r, real_t(imageRect.getTop()) / imageH_r,
				real_t(imageRect.getLeft()) / imageW_r,  real_t(imageRect.getTop()) / imageH_r,
			}
		};
	}

	return rMap;
}

}

SpriteSheet::SpriteSheet(const Image& sourceImage,
                         const std::map<sprite_id_t, Rect<unsigned int>>& spriteAreas)
:	_tex(sourceImage,
 	     Texture::Params { Texture::Params::CLAMP/*_TO_EDGE*/,
								  Texture::Params::CLAMP/*_TO_EDGE*/,
								  Texture::Params::LINEAR,
								  Texture::Params::LINEAR }),
	_texCoords( std::move(convertAreas(sourceImage.getWidth(),
	                                   sourceImage.getHeight(),
	                                   spriteAreas)) )
{
}

const Texture& SpriteSheet::texture() const
{
	return _tex;
}

const std::array<gr::real_t, 8>& SpriteSheet::coordsFor(sprite_id_t spriteID) const
{
	return _texCoords.at(spriteID);
}


}
