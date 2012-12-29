

#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include "gr/Image.hpp"
#include "gr/Texture.hpp"
#include "gr/VertexSupplier.hpp"

#include <text/util.hpp>

#include <array>

namespace gr {

class Sprite : public VertexSupplier
{
public:
	Sprite(const std::array<gr::real_t, 8>& texCoords,
	       const Transform& transform = Transform::identity());

	Transform& transform();
	const Transform& transform() const;

	void writeVertices(VertexWriter& writer);

private:
	const std::array<gr::real_t, 8>& _texCoords;
	Transform _transform;
};

}


#endif /* SPRITE_HPP_ */
