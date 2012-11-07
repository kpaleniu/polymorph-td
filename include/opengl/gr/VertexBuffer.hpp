/**
 * @file VertexList.hpp
 *
 */

#ifndef VERTEXBUFFER_HPP_
#define VERTEXBUFFER_HPP_

#include "gr/opengl.hpp"
#include "gr/types.hpp"
#include "gr/VertexFormat.hpp"

#include "NonCopyable.hpp"

// TODO Check if OpenGL API is available statically.

namespace gr {

class BufferManager;

class VertexBuffer : NonCopyable
{
public:
	VertexBuffer(BufferManager& manager,
	             VertexFormat format,
	             BufferUsage usage,
	             size_t vertexCount);
	~VertexBuffer();

	void writeVertices(size_t offset,
	                   size_t count,
	                   const real* verts);

	void writeColors(size_t offset,
	                 size_t count,
	                 const real* colors);

	void writeTextureCoords(size_t offset,
	                        size_t count,
	                        const real* texCoords);

	void writeNormals(size_t offset,
	                  size_t count,
	                  const real* normals);

	void draw(Primitive primitive);

	//void draw(Primitive primitive, const IndexBuffer& indices); // Not implemented yet.

private:
	void write(size_t offset, size_t size, const real* verts);

	const void* startOf(VertexFormatFlag type) const;

	GLuint _bufferID;
	size_t _vertexCount;

	VertexFormat _vertexFormat;
	BufferManager& _manager;
};

}


#endif /* VERTEXLIST_HPP_ */
