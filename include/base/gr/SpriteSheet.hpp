

#ifndef SPRITESHEET_HPP_
#define SPRITESHEET_HPP_

#include "gr/Image.hpp"
#include "gr/Texture.hpp"

#include <text/util.hpp>

#include <Rect.hpp>
#include <NonCopyable.hpp>

#include <map>

namespace gr {

class SpriteSheet : NonCopyable
{
public:
	typedef text::string_hash sprite_id_t;

	SpriteSheet(const Image& sourceImage,
	            const std::map<sprite_id_t, Rect<unsigned int>>& spriteAreas);

	const Texture& texture() const;

	const std::array<gr::real_t, 8>& coordsFor(sprite_id_t spriteID) const;

private:
	Texture _tex;
	std::map<sprite_id_t, std::array<gr::real_t, 8>> _texCoords;
};

}


#endif /* SPRITESHEET_HPP_ */
