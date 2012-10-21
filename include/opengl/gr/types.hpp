/**
 * @file types.hpp
 *
 */

#ifndef TYPES_HPP_
#define TYPES_HPP_

#include "gr/opengl.hpp"

namespace gr {

typedef GLfloat real;

enum class BufferUsage : GLenum
{
	STATIC = GL_STATIC_DRAW,
	DYNAMIC = GL_DYNAMIC_DRAW,
	STREAM = GL_STREAM_DRAW,
};

}


#endif /* TYPES_HPP_ */
