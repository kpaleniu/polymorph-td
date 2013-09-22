/**
 * @file IndexBuffer.cpp
 *
 */

#include "gr/IndexBuffer.hpp"

#include "gr/GraphicsException.hpp"

#include <Assert.hpp>
#include <Debug.hpp>

namespace gr {

namespace {
const char* TAG = "IndexBuffer";
}

IndexBuffer::IndexBuffer(BufferUsage usage,
        	             size_t indexCount,
        	             const index_t* data)
:	_bufferID(0),
 	_usage(usage),
	_indexCount(indexCount)
{
	if (indexCount > 0)
	{
		gl::genBuffers(1, &_bufferID);
		gl::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferID);

		gl::bufferData(GL_ELEMENT_ARRAY_BUFFER,
					 _indexCount * sizeof(index_t),
					 data,
					 usage);

		GLint bufferSize = 0;
		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);

		DEBUG_OUT(TAG, "Allocated IndexBuffer %i: %i bytes.", _bufferID, bufferSize);

		if ( bufferSize != GLint(_indexCount * sizeof(index_t)) )
		{
			gl::deleteBuffers(1, &_bufferID);
			_bufferID = 0;

			gl::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			throw GraphicsException();
		}

		gl::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

IndexBuffer::IndexBuffer(IndexBuffer&& indexBuffer)
:	_bufferID(indexBuffer._bufferID),
    _usage(indexBuffer._usage),
 	_indexCount(indexBuffer._indexCount)
{
	indexBuffer._bufferID = 0;
}

IndexBuffer::~IndexBuffer()
{
	if (_bufferID != 0)
	{
		gl::deleteBuffers(1, &_bufferID);
		DEBUG_OUT(TAG, "Deallocated IndexBuffer %i", _bufferID);
		_bufferID = 0;
	}
}

void IndexBuffer::writeIndices(size_t offset, size_t size, const index_t* indices)
{
	ASSERT(_bufferID != 0,
	       "Buffer is invalid.");
	ASSERT(offset < _indexCount,
	       "Buffer overflow.");

	gl::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferID);
	gl::bufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset * sizeof(index_t), size * sizeof(index_t), indices);
	gl::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

size_t IndexBuffer::getIndexCount() const
{
	return _indexCount;
}

BufferUsage IndexBuffer::getBufferUsage() const
{
	return _usage;
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other)
{
	if (_bufferID != 0)
		gl::deleteBuffers(1, &_bufferID);

	_bufferID = other._bufferID;
	_indexCount = other._indexCount;

	other._bufferID = 0;
	other._indexCount = 0;

	return *this;
}

}
