/**
 * @file AutoInputStream.hpp
 *
 */

#ifndef CYCLIC_AUTO_INPUT_STREAM_HPP_
#define CYCLIC_AUTO_INPUT_STREAM_HPP_

#include "stream/Buffer.hpp"

namespace stream {

class CyclicAutoInputStream
{
public:
	/**
	 * Constructor.
	 *
	 * @param source	Input to use.
	 */
	CyclicAutoInputStream(Buffer &source);
	/**
	 * Destructor.
	 */
	virtual ~CyclicAutoInputStream();

	/**
	 * Reads an object from the stream.
	 *
	 * @param data	Object to write to.
	 * @return		This.
	 */
	template<typename T>
	CyclicAutoInputStream &operator>>(T &data);

	/**
	 * @returns		The current buffer reading offset.
	 */
	size_t getReadPos() const;

protected:
	/**
	 * Reads data from the buffer.
	 *
	 * @param data	Data to write to.
	 * @param size	Size in bytes of data.
	 */
	virtual void read(void *data, size_t size);

private:
	/**
	 * Buffer with data to read from.
	 */
	Buffer &_source;

	size_t _readOff;
};

// Template implementation

template<typename T>
CyclicAutoInputStream &CyclicAutoInputStream::operator>>(T &data)
{
	read(&data, sizeof(data));
	return *this;
}

}

#endif
