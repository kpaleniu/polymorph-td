#include "Endianess.hpp"

#include <cstring>

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
Scalar flipEndianess(Scalar val)
{
	static_assert(std::is_scalar<Scalar>::value, "Template isn't scalar.");

	union
	{
		Scalar scalar;
		unsigned char ucArr[sizeof(Scalar)];
	} sourceBuffer, targetBuffer;

	sourceBuffer.scalar = val;

	for (int i = 0; i < sizeof(Scalar); ++i)
		targetBuffer.ucArr[i] = sourceBuffer.ucArr[sizeof(Scalar) - 1 - i];

	return targetBuffer.scalar;
}