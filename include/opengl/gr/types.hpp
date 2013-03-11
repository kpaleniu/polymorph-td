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

// OpenGL expects column-major matrices
typedef math::Projection<real_t, false>	Projection;
typedef math::Transform<real_t, false> 	Transform;
typedef math::Matrix<real_t, 2, 1> 		Vector2_r;
typedef math::Matrix<real_t, 3, 1> 		Vector3_r;

namespace detail {

typedef struct {} MODELSPACE_TAG;
typedef struct {} VIEWSPACE_TAG;
typedef struct {} SURFACESPACE_TAG;
typedef struct {} SCREENSPACE_TAG;
typedef struct {} CLIPSPACE_TAG;

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
typedef detail::SpaceVector<detail::CLIPSPACE_TAG, Vector3_r> ClipVector;

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

const std::string& getEnumName(GLenum en);

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

// Array handling
void vertexPointer(GLuint dim, GLenum type, GLuint offset, const void* data);
void colorPointer(GLuint dim, GLenum type, GLuint offset, const void* data);
void texCoordPointer(GLuint dim, GLenum type, GLuint offset, const void* data);
void normalPointer(GLenum type, GLuint offset, const void* data);
//

// State handling
void enableClientState(GLenum type);
void disableClientState(GLenum type);
void enable(GLenum type);
void disable(GLenum type);
//

// Matrix handling
void matrixMode(GLenum type);
void loadMatrix(const float* mat);
void multMatrix(const float* mat);
//

// Framebuffer handling
void clear(GLbitfield mask);
//

// Implementation:

inline void vertex(gr::real_t x, gr::real_t y)
{
	if (LOG_CALLS)
		VERBOSE_OUT(TAG,
		            "glVertex2f(%f, %f)",
		            x,
		            y);

	glVertex2f(x, y);
}
inline void vertex(gr::real_t x, gr::real_t y, gr::real_t z)
{
	if (LOG_CALLS)
		VERBOSE_OUT(TAG,
		            "glVertex3f(%f, %f, %f)",
		            x,
		            y,
		            z);

	glVertex3f(x, y, z);
}
inline void vertex(gr::real_t x, gr::real_t y, gr::real_t z, gr::real_t w)
{
	if (LOG_CALLS)
		VERBOSE_OUT(TAG,
		            "glVertex4f(%f, %f, %f, %f)",
		            x,
		            y,
		            z,
		            w);

	glVertex4f(x, y, z, w);
}
inline void begin(gr::Primitive primitive)
{
	if (LOG_CALLS)
		VERBOSE_OUT(TAG,
		            "glBegin(%s)",
		            getEnumName(GLenum(primitive)).c_str());

	glBegin(GLenum(primitive));

	if (ASSERT_NO_ERRORS)
		assertNoGLError();
}
inline void end()
{
	if (LOG_CALLS)
		VERBOSE_OUT(TAG, "glEnd()");

	glEnd();

	if (ASSERT_NO_ERRORS)
		assertNoGLError();
}
inline void genBuffers(GLuint count, GLuint* ids)
{
	if (LOG_CALLS)
		VERBOSE_OUT(TAG,
		            "glGenBuffers(%i, %p)",
		            count,
		            ids);

	glGenBuffers(count, ids);

	if (ASSERT_NO_ERRORS)
		assertNoGLError();
}
inline void bindBuffer(GLenum type, GLuint id)
{
	if (LOG_CALLS)
		VERBOSE_OUT(TAG,
		            "glBindBuffer(%s, %i)",
		            getEnumName(type).c_str(),
		            id);

	glBindBuffer(type, id);

	if (ASSERT_NO_ERRORS)
		assertNoGLError();
}
inline void bufferData(GLenum type, GLsizei size, const GLvoid* data, gr::BufferUsage usage)
{
	if (LOG_CALLS)
		VERBOSE_OUT(TAG,
		            "glBufferData(%s, %u, %p, %s)",
		            getEnumName(type).c_str(),
		            size,
		            data,
		            getEnumName(GLenum(usage)).c_str());

	glBufferData(type, size, data, GLenum(usage));

	if (ASSERT_NO_ERRORS)
		assertNoGLError();
}
inline void bufferSubData(GLenum type, GLuint offset, GLsizei size, const GLvoid* data)
{
	if (LOG_CALLS)
		VERBOSE_OUT(TAG,
		            "glBufferSubData(%s, %i, %i, %p)",
		            getEnumName(type).c_str(),
		            offset,
		            size,
		            data);

	glBufferSubData(type, offset, size, data);

	if (ASSERT_NO_ERRORS)
		assertNoGLError();
}
inline void deleteBuffers(GLuint count, const GLuint* ids)
{
	if (LOG_CALLS)
		VERBOSE_OUT(TAG,
		            "glDeleteBuffer(%u, %p)",
		            count,
		            ids);

	glDeleteBuffers(count, ids);

	if (ASSERT_NO_ERRORS)
		assertNoGLError();
}
inline void vertexPointer(GLuint dim, GLenum type, GLuint offset, const void* data)
{
	if (LOG_CALLS)
		VERBOSE_OUT(TAG,
		            "glVertexPointer(%u, %s, %u, %p)",
		            dim,
		            getEnumName(type).c_str(),
		            offset,
		            data);

	glVertexPointer(dim, type, offset, data);
}
inline void colorPointer(GLuint dim, GLenum type, GLuint offset, const void* data)
{
	if (LOG_CALLS)
		VERBOSE_OUT(TAG,
		            "glColorPointer(%u, %s, %u, %p)",
		            dim,
		            getEnumName(type).c_str(),
		            offset,
		            data);

	glColorPointer(dim, type, offset, data);
}
inline void texCoordPointer(GLuint dim, GLenum type, GLuint offset, const void* data)
{
	if (LOG_CALLS)
		VERBOSE_OUT(TAG,
		            "glTexCoordPointer(%u, %s, %u, %p)",
		            dim,
		            getEnumName(type).c_str(),
		            offset,
		            data);

	glTexCoordPointer(dim, type, offset, data);
}
inline void normalPointer(GLenum type, GLuint offset, const void* data)
{
	if (LOG_CALLS)
		VERBOSE_OUT(TAG,
		            "glNormalPointer(%s, %u, %p)",
		            getEnumName(type).c_str(),
		            offset,
		            data);

	glNormalPointer(type, offset, data);
}
inline void enableClientState(GLenum type)
{
	if (LOG_CALLS)
		VERBOSE_OUT(TAG,
		            "glEnableClientState(%i)",
		            getEnumName(type).c_str());

	glEnableClientState(type);
}
inline void disableClientState(GLenum type)
{
	if (LOG_CALLS)
		VERBOSE_OUT(TAG,
		            "glDisableClientState(%i)",
		            getEnumName(type).c_str());

	glDisableClientState(type);
}
inline void enable(GLenum type)
{
	if (LOG_CALLS)
		VERBOSE_OUT(TAG,
		            "glEnable(%s)",
		            getEnumName(type));
	glEnable(type);

	if (ASSERT_NO_ERRORS)
		assertNoGLError();
}
inline void disable(GLenum type)
{
	if (LOG_CALLS)
		VERBOSE_OUT(TAG,
		            "glDisable(%s)",
		            getEnumName(type));

	glDisable(type);

	if (ASSERT_NO_ERRORS)
		assertNoGLError();
}
inline void matrixMode(GLenum type)
{
	if (LOG_CALLS)
		VERBOSE_OUT(TAG,
		            "glMatrixMode(%s)",
		            getEnumName(type));

	glMatrixMode(type);

	if (ASSERT_NO_ERRORS)
		assertNoGLError();
}
inline void loadMatrix(const gr::real_t* mat)
{
	if (LOG_CALLS)
		VERBOSE_OUT(TAG,
		            "glLoadMatrixf(%5.2f %5.2f %5.2f %5.2f\n\
              %5.2f %5.2f %5.2f %5.2f\n\
              %5.2f %5.2f %5.2f %5.2f\n\
              %5.2f %5.2f %5.2f %5.2f)",
		             mat[0], mat[4], mat[8],  mat[12],
		             mat[1], mat[5], mat[9],  mat[13],
		             mat[2], mat[6], mat[10], mat[14],
		             mat[3], mat[7], mat[11], mat[15]);

	glLoadMatrixf(mat);

	if (ASSERT_NO_ERRORS)
		assertNoGLError();
}
inline void multMatrix(const gr::real_t* mat)
{
	if (LOG_CALLS)
		VERBOSE_OUT(TAG,
		            "glMultMatrixf(%5.2f %5.2f %5.2f %5.2f\n\
              %5.2f %5.2f %5.2f %5.2f\n\
              %5.2f %5.2f %5.2f %5.2f\n\
              %5.2f %5.2f %5.2f %5.2f)",
	             mat[0], mat[4], mat[8],  mat[12],
	             mat[1], mat[5], mat[9],  mat[13],
	             mat[2], mat[6], mat[10], mat[14],
	             mat[3], mat[7], mat[11], mat[15]);

	glMultMatrixf(mat);

	if (ASSERT_NO_ERRORS)
		assertNoGLError();
}
inline void clear(GLbitfield mask)
{
	if (LOG_CALLS)
		VERBOSE_OUT(TAG,
		            "glClear(%u)",
		            mask);

	glClear(mask);

	if (ASSERT_NO_ERRORS)
		assertNoGLError();
}

}


#endif /* TYPES_HPP_ */
