#pragma once

#include "gr/opengl.hpp"
#include "gr/types.hpp"
#include "gr/VertexFormat.hpp"
#include "gr/IndexBuffer.hpp"

#include <NonCopyable.hpp>

namespace polymorph { namespace gr {

class BufferManager;

class VertexBuffer : NonCopyable
{
public:
	VertexBuffer(VertexFormat format,
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

	bool isEmpty() const;

private:
	void write(size_t offset, size_t size, const real_t* verts);

	void setArrays(const VertexFormatData& formatData);

	const void* startOf(VertexFormatFlag type) const;

	GLuint _bufferID;
	size_t _vertexCount;

	BufferUsage _usage;

	VertexFormat _vertexFormat;
};

} }
