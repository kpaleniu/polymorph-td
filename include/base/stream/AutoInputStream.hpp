/**
 * @file AutoInputStream.hpp
 *
 */

#ifndef AUTOINPUTSTREAM_HPP_
#define AUTOINPUTSTREAM_HPP_

#include <cstddef>

namespace stream {

/**
 * Base class for input streams that reads any type of data.
 */
class AutoInputStream
{
public:
	virtual ~AutoInputStream() {};

	/**
	 * Reads one instance.
	 *
	 * @param data	Target to read to.
	 * @returns 	Reference to this stream.
	 */
	template<typename T>
	AutoInputStream &operator>>(T &data);

	/**
	 *
	 */
	virtual void read(void *data, size_t size) = 0;
};

// Template implementation

template<typename T>
AutoInputStream &AutoInputStream::operator>>(T &data)
{
	read(&data, sizeof(data));
	return *this;
}

}

#endif
