/**
 * @file types.hpp
 *
 */

#ifndef TYPES_HPP_
#define TYPES_HPP_

#include "gr/opengl.hpp"

namespace gr {

typedef GLfloat real;

const GLenum REAL_TYPE = GL_FLOAT;

enum class BufferUsage : GLenum
{
	STATIC = GL_STATIC_DRAW,
	DYNAMIC = GL_DYNAMIC_DRAW,
	STREAM = GL_STREAM_DRAW,
};

enum class Primitive : GLenum
{
	LINES = GL_LINES,
	TRIANGLES = GL_TRIANGLES,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	QUADS = GL_QUADS,
};

}


#endif /* TYPES_HPP_ */
