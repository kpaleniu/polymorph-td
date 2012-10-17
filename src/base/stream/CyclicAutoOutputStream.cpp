/**
 * @file CyclicAutoOutputStream.cpp
 *
 */

#include "stream/CyclicAutoOutputStream.hpp"

#include "Debug.hpp"

namespace stream {

CyclicAutoOutputStream::CyclicAutoOutputStream(size_t size)
		: _source(size), _writeOff(0)
{
	//
}

CyclicAutoOutputStream::~CyclicAutoOutputStream()
{
	//
}

size_t CyclicAutoOutputStream::getWritePos() const
{
	return _writeOff;
}

void CyclicAutoOutputStream::write(const void *data, size_t size)
{
	// Note, end of buffer may contain garbage.
	if (_writeOff + size > _source.getSize())
		_writeOff = 0;

	_writeOff = _source.write(data, size, _writeOff);

	VERBOSE_OUT("CyclicAutoOutputStream", "Write offset = %1%", _writeOff);
}


}
