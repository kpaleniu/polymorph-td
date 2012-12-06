/**
 * @file VertexList.hpp
 *
 */

#ifndef VERTEXBUFFER_HPP_
#define VERTEXBUFFER_HPP_

#include "gr/opengl.hpp"
#include "gr/types.hpp"
#include "gr/VertexFormat.hpp"
#include "gr/IndexBuffer.hpp"

#include <NonCopyable.hpp>

// TODO Check if OpenGL API is available statically.

namespace gr {

class BufferManager;

class VertexBuffer : NonCopyable
{
public:
	VertexBuffer(BufferManager& manager,
	             VertexFormat format,
	             BufferUsage usage,
	             size_t vertexCount=0,
	             const real_t* data=nullptr);

	VertexBuffer(VertexBuffer&& vertexBuffer);

	~VertexBuffer();

	void writeVertices(size_t offset,
	                   size_t count,
	                   const real_t* verts);

	void writeColors(size_t offset,
	                 size_t count,
	                 const real_t* colors);

	void writeTextureCoords(size_t offset,
	                        size_t count,
	                        const real_t* texCoords);

	void writeNormals(size_t offset,
	                  size_t count,
	                  const real_t* normals);

	void draw(Primitive primitive);

	void draw(Primitive primitive,
	          size_t start,
	          size_t end);

	void draw(Primitive primitive,
	          IndexBuffer& indices);

	size_t 		 getVertexCount()  const;
	VertexFormat getVertexFormat() const;
	BufferUsage  getBufferUsage()  const;

	BufferManager& bufferManager();

	VertexBuffer& operator=(VertexBuffer&& other);

private:
	void write(size_t offset, size_t size, const real_t* verts);

	void setArrays(const VertexFormatData& formatData);

	const void* startOf(VertexFormatFlag type) const;

	GLuint _bufferID;
	size_t _vertexCount;

	BufferUsage _usage;

	VertexFormat _vertexFormat;
	BufferManager& _manager;
};

}


#endif /* VERTEXLIST_HPP_ */
