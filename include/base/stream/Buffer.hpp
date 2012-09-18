/**
 * @file Buffer.hpp
 *
 * Contains interface for class Buffer.
 */

#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "StreamException.hpp"

namespace stream {

/**
 * Class providing low-level read and write operations to an array.
 * Note, implementation uses memcpy to read and write memory to and from array.
 */
class Buffer
{
public:
	/**
	 * Constructor.
	 *
	 * @param size	Size in bytes of the buffer.
	 */
	Buffer(size_t size);
	/**
	 * Destructor.
	 */
	~Buffer();

	/**
	 * Writes data to buffer at the specified offset.
	 *
	 * @param src		Source of data to copy.
	 * @param size		Number of bytes to write.
	 * @param offset	The specified offset.
	 * @return			The offset past the newly written data.
	 *
	 * @throws StreamException	If there's not enough room to write.
	 */
	size_t write(const void *src, size_t size, size_t offset);

	/**
	 * Reads data from buffer at the specified offset.
	 *
	 * @param target	Target to write data to.
	 * @param size		Number of bytes to read.
	 * @return			The offset past the read data.
	 *
	 * @throws StreamException	If offset is too high.
	 */
	size_t read(void *target, size_t size, size_t offset) const;

	/**
	 * @returns	The beginning of the array storing the data.
	 */
	const void *begin() const;
	/**
	 * @returns The end of the array storing the data.
	 */
	const void *end() const;

	/**
	 * @returns	The size of the buffer.
	 */
	size_t getSize() const;

private:
	void *_begin;
	void *_end;
};

}

#endif
