#ifndef IO_STREAM_HPP_
#define IO_STREAM_HPP_

#include "io/IOException.hpp"

#include <NonCopyable.hpp>
#include <memory>

namespace io {

class InputStream : NonCopyable
{
public:
	virtual ~InputStream() {}
	
	/**
	 * Returns the amount of bytes left in stream.
	 * May throw io::IOexception if unable to determine.
	 */
	virtual std::size_t available() const = 0;

	/**
	 * May throw io::IOException if unable to read data.
	 */
	template <typename TriviallyCopyable>
	InputStream& operator>>(TriviallyCopyable& data);
	
	/**
	 * May throw io::IOException if unable to read data.
	 */
	template <typename TriviallyCopyable>
	InputStream& readBlock(TriviallyCopyable& data, std::size_t size);

protected:
	virtual void read(void* data, 
					  std::size_t typeAlignment, 
					  std::size_t size, 
					  std::size_t count) = 0;
};

class OutputStream : NonCopyable
{
public:
	virtual ~OutputStream() {}
	
	template <typename TriviallyCopyable>
	OutputStream& operator<<(const TriviallyCopyable& data);

	template <typename TriviallyCopyable>
	OutputStream& operator<<(const std::pair<const TriviallyCopyable&, std::size_t>& dataCollection);
	
protected:
	virtual void write(const void* data, 
					   std::size_t alignment, 
					   std::size_t size, 
					   std::size_t count) = 0;
};


}


#include "io/IOStream.inl"

#endif