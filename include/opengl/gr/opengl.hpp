/**
 * @file opengl.hpp
 *
 */

#ifndef OPENGL_HPP_
#define OPENGL_HPP_

// OpenGL includes here

#ifdef _WIN32
#	include <windows.h>
#	include <gl/glew.h>
#endif

#include <Debug.hpp>

#include "gr/types.hpp"

// Wrapper to OpenGL.
namespace gl {

constexpr const char* TAG = "OpenGL";

constexpr bool LOG_CALLS = true;
constexpr bool ASSERT_NO_ERRORS = true; // Does not affect GL_OUT_OF_MEMORY.
constexpr bool CHECK_OUT_OF_MEMORY = true;

void assertNoGLError();

// Direct rendering
void vertex(gr::real_t x, gr::real_t y);
void vertex(gr::real_t x, gr::real_t y, gr::real_t z);
void vertex(gr::real_t x, gr::real_t y, gr::real_t z);
void vertex(gr::real_t x, gr::real_t y, gr::real_t z, gr::real_t w);

void begin(gr::Primitive primitive);
void end();
//

// Buffer handling
void genBuffers(GLuint count, GLuint* ids);
void bindBuffer(GLenum type, GLuint id);
void bufferData(GLenum type, GLsizei size, const GLvoid* data, gr::BufferUsage usage);
void bufferSubData(GLenum type, GLuint offset, GLsizei size, const GLvoid* data);
void deleteBuffers(GLuint count, const GLuint* ids);
//


//
void vertexPointer(GLuint dim, GLenum type, GLuint offset, const void* data);
void colorPointer(GLuint dim, GLenum type, GLuint offset, const void* data);
void texCoordPointer(GLuint dim, GLenum type, GLuint offset, const void* data);
void normalPointer(GLenum type, GLuint offset, const void* data);
//

//
void enableClientState(GLenum type);
void disableClientState(GLenum type);
//

// Implementation:

inline void vertex(gr::real_t x, gr::real_t y)
{
	if (LOG_CALLS) VERBOSE_OUT(TAG, "glVertex2f(%f, %f)", x, y);
	glVertex2f(x, y);
}
inline void vertex(gr::real_t x, gr::real_t y, gr::real_t z)
{
	if (LOG_CALLS) VERBOSE_OUT(TAG, "glVertex3f(%f, %f, %f)", x, y, z);
	glVertex3f(x, y, z);
}
inline void vertex(gr::real_t x, gr::real_t y, gr::real_t z, gr::real_t w)
{
	if (LOG_CALLS) VERBOSE_OUT(TAG, "glVertex4f(%f, %f, %f, %f)", x, y, z, w);
	glVertex4f(x, y, z, w);
}
inline void begin(gr::Primitive primitive)
{
	if (LOG_CALLS) VERBOSE_OUT(TAG, "glBegin(%i)", int(primitive));
	glBegin(GLenum(primitive));
	if (ASSERT_NO_ERRORS) assertNoGLError();
}
inline void end()
{
	if (LOG_CALLS) VERBOSE_OUT(TAG, "glEnd()");
	glEnd();
	if (ASSERT_NO_ERRORS) assertNoGLError();
}
inline void genBuffers(GLuint count, GLuint* ids)
{
	if (LOG_CALLS) VERBOSE_OUT(TAG, "glGenBuffers(%i, %p)", count, ids);
	glGenBuffers(count, ids);
	if (ASSERT_NO_ERRORS) assertNoGLError();
}
inline void bindBuffer(GLenum type, GLuint id)
{
	if (LOG_CALLS) VERBOSE_OUT(TAG, "glBindBuffer(%i, %i)", type, id);
	glBindBuffer(type, id);
	if (ASSERT_NO_ERRORS) assertNoGLError();
}
inline void bufferData(GLenum type, GLsizei size, const GLvoid* data, gr::BufferUsage usage)
{
	if (LOG_CALLS) VERBOSE_OUT(TAG, "glBufferData(%i, %u, %p, %i)", type, size, data, GLenum(usage));
	glBufferData(type, size, data, GLenum(usage));
	if (ASSERT_NO_ERRORS) assertNoGLError();
}
inline void bufferSubData(GLenum type, GLuint offset, GLsizei size, const GLvoid* data)
{
	if (LOG_CALLS) VERBOSE_OUT(TAG, "glBufferSubData(%i, %i, %i, %p)", type, offset, size, data);
	glBufferSubData(type, offset, size, data);
	if (ASSERT_NO_ERRORS) assertNoGLError();
}
inline void deleteBuffers(GLuint count, const GLuint* ids)
{
	if (LOG_CALLS) VERBOSE_OUT(TAG, "glDeleteBuffer(%u, %p)", count, ids);
	glDeleteBuffers(count, ids);
	if (ASSERT_NO_ERRORS) assertNoGLError();
}
inline void vertexPointer(GLuint dim, GLenum type, GLuint offset, const void* data)
{
	if (LOG_CALLS) VERBOSE_OUT(TAG, "glVertexPointer(%u, %i, %u, %p)", dim, type, offset, data);
	glVertexPointer(dim, type, offset, data);
}
inline void colorPointer(GLuint dim, GLenum type, GLuint offset, const void* data)
{
	if (LOG_CALLS) VERBOSE_OUT(TAG, "glColorPointer(%u, %i, %u, %p)", dim, type, offset, data);
	glColorPointer(dim, type, offset, data);
}
inline void texCoordPointer(GLuint dim, GLenum type, GLuint offset, const void* data)
{
	if (LOG_CALLS) VERBOSE_OUT(TAG, "glTexCoordPointer(%u, %i, %u, %p)", dim, type, offset, data);
	glTexCoordPointer(dim, type, offset, data);
}
inline void normalPointer(GLenum type, GLuint offset, const void* data)
{
	if (LOG_CALLS) VERBOSE_OUT(TAG, "glNormalPointer(%i, %u, %p)", type, offset, data);
	glNormalPointer(type, offset, data);
}
inline void enableClientState(GLenum type)
{
	if (LOG_CALLS) VERBOSE_OUT(TAG, "glEnableClientState(%i)", type);
	glEnableClientState(type);
}
inline void disableClientState(GLenum type)
{
	if (LOG_CALLS) VERBOSE_OUT(TAG, "glDisableClientState(%i)", type);
	glDisableClientState(type);
}
}

#endif /* OPENGL_HPP_ */
