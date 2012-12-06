
#include "gr/opengl.hpp"

#include <Assert.hpp>
#include <Debug.hpp>

namespace gl {

void assertNoGLError()
{
#ifdef _DEBUG
	auto err = glGetError();

	switch (err)
	{
	case GL_INVALID_ENUM:
		DEBUG_OUT(TAG, "INVALID_ENUM");
		break;
	case GL_INVALID_VALUE:
		DEBUG_OUT(TAG, "INVALID_VALUE");
		break;
	case GL_INVALID_OPERATION:
		DEBUG_OUT(TAG, "INVALID OPERATION");
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		DEBUG_OUT(TAG, "INVALID_FRAMEBUFFER_OPERATION?");
		break;
	case GL_OUT_OF_MEMORY:
		DEBUG_OUT(TAG, "OUT_OF_MEMORY");
		break;
	case GL_STACK_UNDERFLOW:
		DEBUG_OUT(TAG, "STACK_UNDERFLOW");
		break;
	case GL_STACK_OVERFLOW:
		DEBUG_OUT(TAG, "STACK_OVERFLOW");
		break;
	}

	ASSERT(err == GL_NO_ERROR,
	       "OpenGL error.");
#endif
}

}
