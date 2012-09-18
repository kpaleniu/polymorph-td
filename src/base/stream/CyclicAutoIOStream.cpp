/**
 * @file CyclicAutoIOStream.cpp
 *
 */

#include "stream/CyclicAutoIOStream.hpp"

#include "Debug.hpp"

namespace stream {

CyclicAutoIOStream::CyclicAutoIOStream(size_t size)
		: CyclicAutoOutputStream(size),
		  CyclicAutoInputStream(CyclicAutoOutputStream::_source),
		  _count(0)
{
	//
}

CyclicAutoIOStream::~CyclicAutoIOStream()
{
	//
}

void CyclicAutoIOStream::write(const void *data,
                               size_t size)
{
	if (_count + size
	    > CyclicAutoOutputStream::_source.getSize())
	{
		DEBUG_OUT_UNIT(CYCLIC_AUTO_IO_STREAM_UNIT,
		               "Thrown StreamException while writing");
		DEBUG_OUT_UNIT(CYCLIC_AUTO_IO_STREAM_UNIT,
		               "count: " << _count);
		DEBUG_OUT_UNIT(CYCLIC_AUTO_IO_STREAM_UNIT,
		               "data size: " << size);
		DEBUG_OUT_UNIT(CYCLIC_AUTO_IO_STREAM_UNIT,
		               "buffer size: " << CyclicAutoOutputStream::_source.getSize());

		throw StreamException("Circular buffer overflow");
	}

	_count += size;
	CyclicAutoOutputStream::write(data, size);
}

void CyclicAutoIOStream::read(void *data,
                              size_t size)
{
	if (_count < size)
	{
		DEBUG_OUT_UNIT(CYCLIC_AUTO_IO_STREAM_UNIT,
		               "Thrown StreamException while reading");
		DEBUG_OUT_UNIT(CYCLIC_AUTO_IO_STREAM_UNIT,
		               "count: " << _count);
		DEBUG_OUT_UNIT(CYCLIC_AUTO_IO_STREAM_UNIT,
		               "data size: " << size);
		DEBUG_OUT_UNIT(CYCLIC_AUTO_IO_STREAM_UNIT,
		               "buffer size: " << CyclicAutoOutputStream::_source.getSize());

		throw StreamException("Circular buffer overflow");
	}

	_count -= size;
	CyclicAutoInputStream::read(data, size);
}

size_t CyclicAutoIOStream::bytesUnread() const
{
	return _count;
}

size_t CyclicAutoIOStream::getSize() const
{
	return CyclicAutoOutputStream::_source.getSize();
}

}

