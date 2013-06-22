
#include "gr/Sprite.hpp"

#include <initializer_list>

namespace gr {

namespace {

// Sprite bounds in model space (counter-clockwise winding order):
const std::array<Vector3_r, 4> spriteBounds =
{
	Vector3_r{-0.5f, -0.5f, 0.0f},
	Vector3_r{ 0.5f, -0.5f, 0.0f},
	Vector3_r{ 0.5f,  0.5f, 0.0f},
	Vector3_r{-0.5f,  0.5f, 0.0f}
};

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
	{
		Vector3_r wr = _transform * vert;
		writer.vertices() << wr[0] << wr[1];
	}

	writer.texCoords() 
		<< _texCoords[0] 
		<< _texCoords[1]
		<< _texCoords[2] 
		<< _texCoords[3]
		<< _texCoords[4]
		<< _texCoords[5] 
		<< _texCoords[6] 
		<< _texCoords[7];

	writer.indices() 
		<< (nextIndex + 0) 
		<< (nextIndex + 1) 
		<< (nextIndex + 2)
		<< (nextIndex + 3);
}

}

