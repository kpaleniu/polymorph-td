#include "Endianess.hpp"

#include <utility>

inline bool isBigEndian()
{
	union
	{
		int i;
		char c[sizeof(int)];
	} temp;

	temp.i = 1;

	return temp.c[sizeof(int) - 1] == 1;
}

inline bool isLittleEndian()
{
	union
	{
		int i;
		char c[sizeof(int)];
	} temp;

	temp.i = 1;

	return temp.c[0] == 1;
}

template <typename Scalar>
inline void flipEndianess(Scalar& val)
{
	static_assert(std::is_scalar<Scalar>::value, "Template isn't scalar.");

	flipEndianess(&val, sizeof(Scalar));
}

inline void flipEndianess(void* data, std::size_t size)
{
	unsigned char* low = reinterpret_cast<unsigned char*>(data);
	unsigned char* high = low + size;

	for (; low < high; ++low, --high)
		std::swap<unsigned char>(*low, *high);
}