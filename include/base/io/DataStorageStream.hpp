#ifndef IO_DATA_STORAGE_STREAM_HPP_
#define IO_DATA_STORAGE_STREAM_HPP_

#include "io/IOStream.hpp"

#include <cstdint>
#include <memory>

namespace io {

class DataStorageInputStream : public InputStream
{
public:
	DataStorageInputStream(const void* data, std::size_t size);
	DataStorageInputStream(DataStorageInputStream&& other);

	std::size_t available() const;

	virtual void read(void* data, 
					  std::size_t typeAlignment, 
					  std::size_t size, 
					  std::size_t count);

protected:
	std::uintptr_t _readPos;
	std::uintptr_t _readEnd;
};


}

#endif