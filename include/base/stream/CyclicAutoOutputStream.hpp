/**
 * @file CyclicAutoOutputStream.hpp
 *
 */

#ifndef CYCLIC_AUTO_OUTPUT_STREAM_HPP_
#define CYCLIC_AUTO_OUTPUT_STREAM_HPP_

#include "stream/AutoOutputStream.hpp"
#include "stream/Buffer.hpp"

namespace stream {

/**
 * Cyclic output stream containing data of any type.
 * The data is stored in a stream::Buffer.
 */
class CyclicAutoOutputStream : public AutoOutputStream
{
public:
	/**
	 * Constructor.
	 *
	 * @param size	Size in bytes of buffer.
	 */
	CyclicAutoOutputStream(size_t size);

	CyclicAutoOutputStream(CyclicAutoOutputStream&& caos);

	/**
	 * Destructor.
	 */
	virtual ~CyclicAutoOutputStream();

	/**
	 * @returns		The current buffer writing offset.
	 */
	size_t getWritePos() const;

	virtual void write(const void *data, size_t size);

protected:
	/**
	 * Buffer storing the data.
	 */
	Buffer _source;

private:
	size_t _writeOff;
};

}

#endif
