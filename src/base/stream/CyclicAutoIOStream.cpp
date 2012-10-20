/**
 * @file CyclicAutoIOStream.cpp
 *
 */

#include "stream/CyclicAutoIOStream.hpp"

#include "Debug.hpp"

namespace stream {
namespace { const char* TAG = "CyclicAutoIOStream"; }

CyclicAutoIOStream::CyclicAutoIOStream(size_t size)
:	CyclicAutoOutputStream(size),
	CyclicAutoInputStream(CyclicAutoOutputStream::_source),
	_count(0)
{
}

CyclicAutoIOStream::CyclicAutoIOStream(CyclicAutoIOStream&& caios)
:	CyclicAutoOutputStream(std::move(caios)),
 	CyclicAutoInputStream(std::move(caios)),
 	_count(caios._count)
{
}

CyclicAutoIOStream::~CyclicAutoIOStream()
{
}

void CyclicAutoIOStream::write(const void *data,
                               size_t size)
{
	if (_count + size
	    > CyclicAutoOutputStream::_source.getSize())
	{
		ERROR_OUT(TAG, "Cyclic buffer overflow while writing!\ncount: %1%\ndata size: %2%\nbuffer size: %3%",
			_count, size, CyclicAutoOutputStream::_source.getSize());
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
		ERROR_OUT(TAG, "Cyclic buffer underflow while reading!\ncount: %1%\ndata size: %2%\nbuffer size: %3%",
			_count, size, CyclicAutoOutputStream::_source.getSize());
		throw StreamException("Circular buffer underflow");
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

