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
std::array<unsigned char, sizeof(Scalar)> copyAsBigEndian(Scalar val)
{
	static_assert(std::is_scalar<Scalar>::value, "Template isn't scalar.");

	std::array<unsigned char, sizeof(Scalar)> rArray;

	if (isBigEndian())
	{
		std::memcpy(rArray.data(), &val, sizeof(Scalar));
	}
	else
	{
		union
		{
			Scalar scalar;
			unsigned char ucArr[sizeof(Scalar)];
		} dataBuffer;

		dataBuffer.scalar = val;

		for (int i = 0; i < sizeof(Scalar); ++i)
			rArray[i] = dataBuffer.ucArr[sizeof(Scalar) - 1 - i];
	}

	return rArray;
}

template <typename Scalar>
std::array<unsigned char, sizeof(Scalar)> copyAsLittleEndian(Scalar val)
{
	static_assert(std::is_scalar<Scalar>::value, "Template isn't scalar.");

	std::array<unsigned char, sizeof(Scalar)> rArray;

	if (isLittleEndian())
	{
		std::memcpy(rArray.data(), &val, sizeof(Scalar));
	}
	else
	{
		union
		{
			Scalar scalar;
			unsigned char ucArr[sizeof(Scalar)];
		} dataBuffer;

		dataBuffer.scalar = val;

		for (int i = 0; i < sizeof(Scalar); ++i)
			rArray[i] = dataBuffer.ucArr[sizeof(Scalar) - 1 - i];
	}

	return rArray;
}