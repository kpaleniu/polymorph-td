/**
 * @file types.hpp
 *
 */

#ifndef GR_TYPES_HPP_
#define GR_TYPES_HPP_

#include "gr/opengl.hpp"

#include <math/Projection.hpp>
#include <math/Transform.hpp>

#include <array>

namespace gr {

typedef GLfloat real_t;
typedef GLuint  index_t;
typedef GLenum 	enum_t;

typedef math::Projection<real_t, true> 	Projection;
typedef math::Transform<real_t, true> 	Transform;
typedef math::Matrix<real_t, 2, 1> 		Vector2_r;
typedef math::Matrix<real_t, 3, 1> 		Vector3_r;

const enum_t REAL_TYPE 	= GL_FLOAT;
const enum_t INDEX_TYPE = GL_UNSIGNED_INT;

enum class BufferUsage : enum_t
{
	STATIC 	= GL_STATIC_DRAW,
	DYNAMIC = GL_DYNAMIC_DRAW,
	STREAM 	= GL_STREAM_DRAW,
};

enum class Primitive : enum_t
{
	LINES 			= GL_LINES,
	TRIANGLES 		= GL_TRIANGLES,
	TRIANGLE_STRIP 	= GL_TRIANGLE_STRIP,
	QUADS 			= GL_QUADS,
};

enum class BufferFlag : enum_t
{
	NONE 		= 0,
	COLOR 		= GL_COLOR_BUFFER_BIT,
	DEPTH		= GL_DEPTH_BUFFER_BIT,
	ALL			= COLOR | DEPTH,
};

}


#endif /* TYPES_HPP_ */
