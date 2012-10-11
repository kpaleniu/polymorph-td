/**
 * @file ArrayInputStream.hpp
 *
 */

#ifndef ARRAYINPUTSTREAM_HPP
#define ARRAYINPUTSTREAM_HPP

#include "stream/StreamException.hpp"

namespace stream {

/**
 * Input stream with array as source.
 */
template<typename T>
class ArrayInputStream
{
public:
	/**
	 * Constructor.
	 *
	 * @param dataBuffer source for input.
	 * @param elementCount elements of the array.
	 */
	ArrayInputStream(const T *dataBuffer, size_t elementCount);

	/**
	 * Reads one element.
	 *
	 * @param data target to write input.
	 * @return this.
	 */
	ArrayInputStream &operator>>(T &data);

	/**
	 * Checks the elements left available to read.
	 *
	 * @return the number of elements left.
	 */
	size_t dataLeft() const;

protected:
	const T *_dataBuffer;
	T *_pos;
};

// Implementation:

template<typename T>
ArrayInputStream<T>::ArrayInputStream(const T *dataBuffer,
                                      size_t elementCount)
		: _dataBuffer(dataBuffer),
		  _pos(dataBuffer + elementCount)
{
}

template<typename T>
ArrayInputStream<T> &ArrayInputStream<T>::operator>>(T &data)
{
	if (_pos - 1 < _dataBuffer)
	{
		throw StreamException("Buffer underflow");
	}

	data = *(--_pos);

	return *this;
}

template<typename T>
size_t ArrayInputStream<T>::dataLeft() const
{
	return _pos - _dataBuffer;
}

}

#endif
