#pragma once

#include "gr/opengl.hpp"

namespace polymorph { namespace gr {

enum class PixelFormat : GLint
{
	R8G8B8		= GL_RGB,
	R8G8B8A8	= GL_RGBA,
};

// PixelFormat getFormat(char rbits, char gbits, char bbits, char abits);

} }