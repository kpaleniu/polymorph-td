/**
 * @file CyclicAutoInputStream.cpp
 *
 */

#include "stream/CyclicAutoInputStream.hpp"

namespace stream {

CyclicAutoInputStream::CyclicAutoInputStream(Buffer &source)
		: _source(source), _readOff(0)
{
	//
}

CyclicAutoInputStream::~CyclicAutoInputStream()
{
	//
}

size_t CyclicAutoInputStream::getReadPos() const
{
	return _readOff;
}

void CyclicAutoInputStream::read(void *data,
                                 size_t size)
{
	if (_readOff + size > _source.getSize())
		_readOff = 0;

	_readOff = _source.read(data, size, _readOff);
}

}
