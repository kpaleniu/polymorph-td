#pragma once

#include "io/IOStream.hpp"

#include <cstdint>
#include <memory>

namespace polymorph { namespace io {

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


} }