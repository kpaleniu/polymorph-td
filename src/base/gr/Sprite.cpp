
#include "gr/Sprite.hpp"

namespace gr {

namespace {

// Sprite bounds in model space (counter-clockwise winding order):
const std::array<Vector3_r, 4> spriteBounds =
{{
	std::array<real_t, 3>{{-0.5f, -0.5f, 0.0f}},
	std::array<real_t, 3>{{ 0.5f, -0.5f, 0.0f}},
	std::array<real_t, 3>{{ 0.5f,  0.5f, 0.0f}},
	std::array<real_t, 3>{{-0.5f,  0.5f, 0.0f}}
}};

}

Sprite::Sprite(const std::array<gr::real_t, 8>& texCoords,
    	       const Transform& transform)
:	_texCoords(texCoords),
 	_transform(transform)
{
}

Transform& Sprite::transform()
{
	return _transform;
}

const Transform& Sprite::transform() const
{
	return _transform;
}

void Sprite::writeVertices(VertexWriter& writer)
{
	size_t nextIndex = writer.getVertexCount();

	for (const Vector3_r& vert : spriteBounds)
		writer.vertices().write( (_transform * vert).data(), 3 );

	writer.texCoords() << _texCoords;

	writer.indices() << std::array<index_t, 4>{{nextIndex + 0,
												nextIndex + 1,
												nextIndex + 2,
												nextIndex + 3}};
}

}

