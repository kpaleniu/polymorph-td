
#include "gr/types.hpp"

#include <Assert.hpp>
#include <Debug.hpp>

#define ERROR_CASE(enumName) case enumName: DEBUG_OUT(LOG_TAG, #enumName); break

namespace gl {

void assertNoGLError()
{
#ifdef _DEBUG
	auto err = glGetError();

	switch (err)
	{
		ERROR_CASE(GL_INVALID_ENUM);
		ERROR_CASE(GL_INVALID_VALUE);
		ERROR_CASE(GL_INVALID_OPERATION);
		ERROR_CASE(GL_INVALID_FRAMEBUFFER_OPERATION);
		ERROR_CASE(GL_OUT_OF_MEMORY);
		ERROR_CASE(GL_STACK_UNDERFLOW);
		ERROR_CASE(GL_STACK_OVERFLOW);
	}

	ASSERT(err == GL_NO_ERROR,
	       "OpenGL error.");
#endif
}

}

#undef ERROR_CASE