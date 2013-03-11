
#include "gr/types.hpp"

#include <Assert.hpp>
#include <Debug.hpp>

#include <map>

namespace gl {

namespace {

#define DEFINE_ENUM_NAME(enumName) { enumName, #enumName }

const std::map<const GLenum, const std::string> enumNames =
{
	DEFINE_ENUM_NAME(GL_STATIC_DRAW),
	DEFINE_ENUM_NAME(GL_DYNAMIC_DRAW),
	DEFINE_ENUM_NAME(GL_LINES),
	DEFINE_ENUM_NAME(GL_TRIANGLES),
	DEFINE_ENUM_NAME(GL_TRIANGLE_STRIP),
	DEFINE_ENUM_NAME(GL_QUADS),
	DEFINE_ENUM_NAME(GL_ARRAY_BUFFER),
	DEFINE_ENUM_NAME(GL_ELEMENT_ARRAY_BUFFER),
	DEFINE_ENUM_NAME(GL_VERTEX_ARRAY),
	DEFINE_ENUM_NAME(GL_FLOAT),
	DEFINE_ENUM_NAME(GL_TEXTURE_2D),
	DEFINE_ENUM_NAME(GL_TEXTURE_COORD_ARRAY),
	DEFINE_ENUM_NAME(GL_PROJECTION),
	DEFINE_ENUM_NAME(GL_MODELVIEW)
};

#undef DEFINE_ENUM_NAME

}

const std::string& getEnumName(GLenum en)
{
	static const std::string badArgument("UNKOWN ENUM");

	try
	{
		return enumNames.at(en);
	}
	catch (std::exception& e)
	{
		return badArgument;
	}
}

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
