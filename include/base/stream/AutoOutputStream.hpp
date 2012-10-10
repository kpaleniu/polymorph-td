/**
 * @file AutoOutputStream.hpp
 *
 */

#ifndef AUTOOUTPUTSTREAM_HPP_
#define AUTOOUTPUTSTREAM_HPP_

#include "NonCopyable.hpp"
#include <cstddef>

namespace stream {

class AutoOutputStream : NonCopyable
{
public:
	virtual ~AutoOutputStream() {}

	/**
	 * Single element write operator.
	 *
	 * @param data	Data to write (note, data is copied by memcpy).
	 * @returns		Reference to this stream.
	 */
	template<typename T>
	AutoOutputStream &operator<<(const T &data);

	/**
	 * Writes data.
	 *
	 * @param data	Pointer to start of data.
	 * @param size	Number of bytes to write.
	 */
	virtual void write(const void *data, size_t size) = 0;
};

// Template implementation

template<typename T>
AutoOutputStream &AutoOutputStream::operator<<(const T &data)
{
	write(&data, sizeof(data));
	return *this;
}

}


#endif /* AUTOOUTPUTSTREAM_HPP_ */
