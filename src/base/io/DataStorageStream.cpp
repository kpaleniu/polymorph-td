#include "io/DataStorageStream.hpp"

#include <Alignment.hpp>
#include <Assert.hpp>

namespace polymorph { namespace io {

DataStorageInputStream::DataStorageInputStream(const void* data, std::size_t size)
:	_readPos(std::uintptr_t(data)), 
	_readEnd(_readPos + size)
{}

DataStorageInputStream::DataStorageInputStream(DataStorageInputStream&& other)
:	_readPos(other._readPos),
	_readEnd(other._readEnd)
{}

void DataStorageInputStream::read(void* data, 
								  std::size_t typeAlignment, 
								  std::size_t size, 
								  std::size_t count)
{
	void* aligned = align(typeAlignment, reinterpret_cast<void*>(_readPos));

	auto bytesToRead = size * count;

	if (std::uintptr_t(aligned) + bytesToRead > _readEnd)
		throw IOException();

	std::memcpy(data, aligned, bytesToRead);

	_readPos = std::uintptr_t(aligned) + bytesToRead;
}

std::size_t DataStorageInputStream::available() const
{
	return std::size_t(_readEnd - _readPos);
}

} }