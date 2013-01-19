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

namespace detail {

typedef struct {} MODELSPACE_TAG;
typedef struct {} VIEWSPACE_TAG;
typedef struct {} SURFACESPACE_TAG;
typedef struct {} SCREENSPACE_TAG;

template <typename SPACETAG, typename V>
class SpaceVector
{
public:
	explicit SpaceVector(const V& vec) : _vec(vec) {}

	explicit operator V() 		 		{ return _vec; }
	explicit operator V() 		 const  { return _vec; }
	explicit operator V&()				{ return _vec; }
	explicit operator const V&() const 	{ return _vec; }

private:
	V _vec;
};

}

typedef detail::SpaceVector<detail::SURFACESPACE_TAG, Vector2_r> SurfaceVector;
typedef detail::SpaceVector<detail::MODELSPACE_TAG, Vector3_r> ModelVector;

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

//////////////

#include <Debug.hpp>

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


#endif /* TYPES_HPP_ */
