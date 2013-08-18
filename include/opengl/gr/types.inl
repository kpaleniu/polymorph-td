#include "gr/types.hpp"

#if LOG_GL_CALLS || ASSERT_NO_GL_ERRORS
#	include <Debug.hpp>
#endif

namespace gl {

#define LOG_TAG "OpenGL"

namespace detail
{
#if LOG_GL_CALLS

#	define ENUM_NAME_CASE(enumName) case enumName: return #enumName

	inline const char* getEnumName(GLenum en)
	{
		switch (en)
		{
			ENUM_NAME_CASE(GL_STATIC_DRAW);
			ENUM_NAME_CASE(GL_DYNAMIC_DRAW);
			ENUM_NAME_CASE(GL_LINES);
			ENUM_NAME_CASE(GL_TRIANGLES);
			ENUM_NAME_CASE(GL_TRIANGLE_STRIP);
			ENUM_NAME_CASE(GL_QUADS);
			ENUM_NAME_CASE(GL_ARRAY_BUFFER);
			ENUM_NAME_CASE(GL_ELEMENT_ARRAY_BUFFER);
			ENUM_NAME_CASE(GL_VERTEX_ARRAY);
			ENUM_NAME_CASE(GL_FLOAT);
			ENUM_NAME_CASE(GL_TEXTURE_2D);
			ENUM_NAME_CASE(GL_TEXTURE_COORD_ARRAY);
			ENUM_NAME_CASE(GL_PROJECTION);
			ENUM_NAME_CASE(GL_MODELVIEW);
		};

		return "<unknown enum name>";
	}
#	undef ENUM_NAME_CASE

#endif

#if ASSERT_NO_GL_ERRORS
#	define ERROR_CASE(enumName) case enumName: DEBUG_OUT(LOG_TAG, #enumName); break

	inline void assertNoGLError()
	{
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
	}

#	undef ERROR_CASE
}

#endif


inline void vertex(gr::real_t x, gr::real_t y)
{
#if LOG_GL_CALLS
	VERBOSE_OUT(LOG_TAG, "glVertex2f(%f, %f)", x, y);
#endif

	glVertex2f(x, y);
}

inline void vertex(gr::real_t x, gr::real_t y, gr::real_t z)
{
#if LOG_GL_CALLS
	VERBOSE_OUT(LOG_TAG, "glVertex3f(%f, %f, %f)", x, y, z);
#endif

	glVertex3f(x, y, z);
}

inline void vertex(gr::real_t x, gr::real_t y, gr::real_t z, gr::real_t w)
{
#if LOG_GL_CALLS
	VERBOSE_OUT(LOG_TAG, "glVertex4f(%f, %f, %f, %f)", x, y, z, w);
#endif

	glVertex4f(x, y, z, w);
}

inline void begin(gr::Primitive primitive)
{
#if LOG_GL_CALLS
	VERBOSE_OUT(LOG_TAG,
		        "glBegin(%s)",
		        detail::getEnumName(GLenum(primitive)));
#endif

	glBegin(GLenum(primitive));

#if ASSERT_NO_GL_ERRORS
	detail::assertNoGLError();
#endif
}

inline void end()
{
#if LOG_GL_CALLS
	VERBOSE_OUT(LOG_TAG, "glEnd()");
#endif

	glEnd();

#if ASSERT_NO_GL_ERRORS
	detail::assertNoGLError();
#endif
}

inline void genBuffers(GLuint count, GLuint* ids)
{
#if LOG_GL_CALLS
	VERBOSE_OUT(LOG_TAG, "glGenBuffers(%i, %p)", count, ids);
#endif

	glGenBuffers(count, ids);

#if ASSERT_NO_GL_ERRORS
	detail::assertNoGLError();
#endif
}

inline void bindBuffer(GLenum type, GLuint id)
{
#if LOG_GL_CALLS
	VERBOSE_OUT(LOG_TAG, "glBindBuffer(%s, %i)", detail::getEnumName(type), id);
#endif

	glBindBuffer(type, id);

#if ASSERT_NO_GL_ERRORS
	detail::assertNoGLError();
#endif
}

inline void bufferData(GLenum type, GLsizei size, const GLvoid* data, gr::BufferUsage usage)
{
#if LOG_GL_CALLS
	VERBOSE_OUT(LOG_TAG,
		        "glBufferData(%s, %u, %p, %s)",
		        detail::getEnumName(type),
		        size,
		        data,
		        detail::getEnumName(GLenum(usage)));
#endif

	glBufferData(type, size, data, GLenum(usage));

#if ASSERT_NO_GL_ERRORS
	detail::assertNoGLError();
#endif
}

inline void bufferSubData(GLenum type, GLuint offset, GLsizei size, const GLvoid* data)
{
#if LOG_GL_CALLS
	VERBOSE_OUT(LOG_TAG,
		        "glBufferSubData(%s, %i, %i, %p)",
		        detail::getEnumName(type),
		        offset,
		        size,
		        data);
#endif

	glBufferSubData(type, offset, size, data);

#if ASSERT_NO_GL_ERRORS
	detail::assertNoGLError();
#endif
}

inline void deleteBuffers(GLuint count, const GLuint* ids)
{
#if LOG_GL_CALLS
	VERBOSE_OUT(LOG_TAG, "glDeleteBuffer(%u, %p)", count, ids);
#endif

	glDeleteBuffers(count, ids);

#if ASSERT_NO_GL_ERRORS
	detail::assertNoGLError();
#endif
}

inline void vertexPointer(GLuint dim, GLenum type, GLuint offset, const void* data)
{
#if LOG_GL_CALLS
	VERBOSE_OUT(LOG_TAG,
		        "glVertexPointer(%u, %s, %u, %p)",
		        dim,
		        detail::getEnumName(type),
		        offset,
	            data);
#endif

	glVertexPointer(dim, type, offset, data);
}

inline void colorPointer(GLuint dim, GLenum type, GLuint offset, const void* data)
{
#if LOG_GL_CALLS
	VERBOSE_OUT(LOG_TAG,
		        "glColorPointer(%u, %s, %u, %p)",
		        dim,
		        detail::getEnumName(type),
		        offset,
		        data);
#endif

	glColorPointer(dim, type, offset, data);
}

inline void texCoordPointer(GLuint dim, GLenum type, GLuint offset, const void* data)
{
#if LOG_GL_CALLS
	VERBOSE_OUT(LOG_TAG,
		        "glTexCoordPointer(%u, %s, %u, %p)",
		        dim,
		        detail::getEnumName(type),
		        offset,
		        data);
#endif

	glTexCoordPointer(dim, type, offset, data);
}

inline void normalPointer(GLenum type, GLuint offset, const void* data)
{
#if LOG_GL_CALLS
	VERBOSE_OUT(LOG_TAG,
		        "glNormalPointer(%s, %u, %p)",
		        detail::getEnumName(type),
		        offset,
		        data);
#endif

	glNormalPointer(type, offset, data);
}

inline void enableClientState(GLenum type)
{
#if LOG_GL_CALLS
		VERBOSE_OUT(LOG_TAG,
		            "glEnableClientState(%i)",
		            detail::getEnumName(type));
#endif

	glEnableClientState(type);
}

inline void disableClientState(GLenum type)
{
#if LOG_GL_CALLS
	VERBOSE_OUT(LOG_TAG,
		        "glDisableClientState(%i)",
		        detail::getEnumName(type));
#endif

	glDisableClientState(type);
}

inline void enable(GLenum type)
{
#if LOG_GL_CALLS
	VERBOSE_OUT(LOG_TAG,
		        "glEnable(%s)",
		        detail::getEnumName(type));
#endif

	glEnable(type);

#if ASSERT_NO_GL_ERRORS
	detail::assertNoGLError();
#endif
}

inline void disable(GLenum type)
{
#if LOG_GL_CALLS
	VERBOSE_OUT(LOG_TAG,
		        "glDisable(%s)",
		        detail::getEnumName(type));
#endif

	glDisable(type);

#if ASSERT_NO_GL_ERRORS
	detail::assertNoGLError();
#endif
}

inline void matrixMode(GLenum type)
{
#if LOG_GL_CALLS
	VERBOSE_OUT(LOG_TAG,
		        "glMatrixMode(%s)",
		        detail::getEnumName(type));
#endif

	glMatrixMode(type);

#if ASSERT_NO_GL_ERRORS
	detail::assertNoGLError();
#endif
}

inline void loadIdentity()
{
#if LOG_GL_CALLS
	VERBOSE_OUT(LOG_TAG, "glLoadIdentity()");
#endif

	glLoadIdentity();
}

inline void loadMatrix(const gr::real_t* mat)
{
#if LOG_GL_CALLS
	VERBOSE_OUT(LOG_TAG,
		        "glLoadMatrixf(%5.2f %5.2f %5.2f %5.2f\n\
            %5.2f %5.2f %5.2f %5.2f\n\
            %5.2f %5.2f %5.2f %5.2f\n\
            %5.2f %5.2f %5.2f %5.2f)",
		            mat[0], mat[4], mat[8],  mat[12],
		            mat[1], mat[5], mat[9],  mat[13],
		            mat[2], mat[6], mat[10], mat[14],
		            mat[3], mat[7], mat[11], mat[15]);
#endif

	glLoadMatrixf(mat);

#if ASSERT_NO_GL_ERRORS
	detail::assertNoGLError();
#endif
}

inline void multMatrix(const gr::real_t* mat)
{
#if LOG_GL_CALLS
	VERBOSE_OUT(LOG_TAG,
		        "glMultMatrixf(%5.2f %5.2f %5.2f %5.2f\n\
            %5.2f %5.2f %5.2f %5.2f\n\
            %5.2f %5.2f %5.2f %5.2f\n\
            %5.2f %5.2f %5.2f %5.2f)",
	            mat[0], mat[4], mat[8],  mat[12],
	            mat[1], mat[5], mat[9],  mat[13],
	            mat[2], mat[6], mat[10], mat[14],
	            mat[3], mat[7], mat[11], mat[15]);
#endif

	glMultMatrixf(mat);

#if ASSERT_NO_GL_ERRORS
	detail::assertNoGLError();
#endif
}

inline void clear(GLbitfield mask)
{
#if LOG_GL_CALLS
	VERBOSE_OUT(LOG_TAG, "glClear(%u)", mask);
#endif

	glClear(mask);

#if ASSERT_NO_GL_ERRORS
	detail::assertNoGLError();
#endif
}

}

#undef LOG_TAG
#undef ASSERT_NO_ERRORS
#undef CHECK_OUT_OF_MEMORY