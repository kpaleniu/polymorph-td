/**
 * @file CyclicAutoIOStream.hpp
 *
 */

#ifndef CYCLICAUTOIOSTREAM_HPP_
#define CYCLICAUTOIOSTREAM_HPP_

#include "stream/CyclicAutoOutputStream.hpp"
#include "stream/CyclicAutoInputStream.hpp"

namespace stream {

/**
 * Cyclic auto input / output stream.
 */
class CyclicAutoIOStream : public CyclicAutoOutputStream,
                           public CyclicAutoInputStream
{
public:
	CyclicAutoIOStream(size_t size);
	virtual ~CyclicAutoIOStream();

	size_t bytesUnread() const;
	size_t getSize() const;

	virtual void write(const void *data, size_t size);
	virtual void read(void *data, size_t size);

private:
	size_t _count; // Number of bytes written but not read.
};

}

#endif
