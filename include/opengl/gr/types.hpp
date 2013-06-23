/**
 * @file types.hpp
 *
 */

#ifndef GR_TYPES_HPP_
#define GR_TYPES_HPP_

#include "gr/opengl.hpp"

#include <math/Projection.hpp>
#include <math/Transform.hpp>
#include <math/Box.hpp>

#include <array>

namespace gr {

typedef GLfloat real_t;
typedef GLuint  index_t;
typedef GLenum 	enum_t;

// OpenGL expects column-major matrices
typedef math::Projection<real_t, false>	Projection;
typedef math::Transform<real_t, false> 	Transform;

typedef math::AxisAlignedBox<real_t, false> AABox;

typedef math::Matrix<real_t, 2, 1> 		Vector2_r;
typedef math::Matrix<real_t, 3, 1> 		Vector3_r;
typedef math::MatrixMap<real_t, 2, 1>	MapVector2_r;
typedef math::MatrixMap<real_t, 3, 1>	MapVector3_r;

typedef math::MatrixMap<real_t, math::DYNAMIC, 1> MapVector_r;

namespace detail {

typedef struct {} MODELSPACE_TAG;
typedef struct {} VIEWSPACE_TAG;
typedef struct {} SURFACESPACE_TAG;
typedef struct {} SCREENSPACE_TAG;
typedef struct {} CLIPSPACE_TAG;
typedef struct {} WORLD_TAG;

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
typedef detail::SpaceVector<detail::WORLD_TAG, Vector3_r> WorldVector;

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
	PRIMITIVE_ENUM_SIZE,
};

enum class BufferFlag : enum_t
{
	NONE 		= 0,
	COLOR 		= GL_COLOR_BUFFER_BIT,
	DEPTH		= GL_DEPTH_BUFFER_BIT,
	ALL			= COLOR | DEPTH,
};

}

#define LOG_GL_CALLS			1
#define CHECK_GL_OUT_OF_MEMORY	1
#define ASSERT_NO_GL_ERRORS		1

// Wrapper to OpenGL.
namespace gl {

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
void loadIdentity();
void loadMatrix(const float* mat);
void multMatrix(const float* mat);
//

// Framebuffer handling
void clear(GLbitfield mask);
//

}

#include "gr/types.inl"

#endif /* TYPES_HPP_ */
