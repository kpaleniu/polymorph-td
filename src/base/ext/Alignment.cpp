#include "Alignment.hpp"

#include "Assert.hpp"
#include <cstdint>


namespace {

// http://stackoverflow.com/questions/600293/how-to-check-if-a-number-is-a-power-of-2

inline bool isPowOf2(std::size_t x)
{
	return (x & (x - 1)) == 0;
}

}

void* align(std::size_t typeAlignment, const void* data)
{
	ASSERT(isPowOf2(typeAlignment), "Alignment isn't power of 2.");

	std::uintptr_t rawPointer = std::uintptr_t(data);

	std::size_t mask = (typeAlignment - 1);
	std::size_t misalignment = (rawPointer & mask);
	std::size_t adjustment = (typeAlignment - misalignment) % typeAlignment;

	std::uintptr_t adjustedPointerRaw = rawPointer + adjustment;

	return reinterpret_cast<void*>(adjustedPointerRaw);
}