#pragma once

#include "gr/opengl.hpp"
#include "gr/types.hpp"

#include "NonCopyable.hpp"

namespace polymorph { namespace gr {

class IndexBuffer : NonCopyable
{
public:
	friend class VertexBuffer;

	IndexBuffer(BufferUsage usage,
	            size_t indexCount=0,
	            const index_t* data=nullptr);

	IndexBuffer(IndexBuffer&& indexBuffer);

	~IndexBuffer();

	void writeIndices(size_t offset, size_t size, const index_t* indices);

	size_t getIndexCount() const;
	BufferUsage getBufferUsage() const;

	IndexBuffer& operator=(IndexBuffer&& other);
private:
	GLuint _bufferID;
	BufferUsage _usage;
	size_t _indexCount;
};

} }
