/**
 * @file Buffer.cpp
 *
 */

#include "stream/Buffer.hpp"

#include <cstdlib>
#include <cstring>

#include "Debug.hpp"

namespace stream {
namespace { const char* TAG = "Buffer"; }

Buffer::Buffer(size_t size)
:	_begin(malloc(size)),
	_end((char *) (_begin) + size)
{
}

Buffer::Buffer(const Buffer& buffer)
:	_begin(malloc(buffer.getSize())),
 	_end((char*) (_begin) + buffer.getSize())
{
	memcpy(_begin, buffer._begin, buffer.getSize());

	DEBUG_OUT(TAG, "Warning, copying buffer");
}

Buffer::Buffer(Buffer&& buffer)
:	_begin(buffer._begin),
 	_end(buffer._end)
{
	buffer._begin = nullptr;
	buffer._end = nullptr;
}

Buffer::~Buffer()
{
	if (_begin != nullptr)
		free(_begin);
}

size_t Buffer::write(const void *src,
                     size_t size,
                     size_t offset)
{
	if (size_t(_begin) + offset + size
	    > size_t(_end))
		throw StreamException("Buffer overflow");

	memcpy((void *) (size_t(_begin) + offset),
	       src,
	       size);

	VERBOSE_OUT(TAG, "Wrote %1% bytes to %2%", size, offset);

	return offset + size;
}

size_t Buffer::read(void *target,
                    size_t size,
                    size_t offset) const
{
	if (size_t(_begin) + offset + size
	    > size_t(_end))
		throw StreamException("Buffer index out of bounds");

	memcpy(target,
	       (void *) (size_t(_begin) + offset),
	       size);

	VERBOSE_OUT(TAG, "Read %1% bytes from %2%", size, offset);

	return offset + size;
}

const void *Buffer::begin() const
{
	return _begin;
}

const void *Buffer::end() const
{
	return _end;
}

size_t Buffer::getSize() const
{
	return size_t(_end) - size_t(_begin);
}

}

