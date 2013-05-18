#ifndef ENDIANESS_HPP_
#define ENDIANESS_HPP_

#include <array>
#include <type_traits>

inline bool isBigEndian();
inline bool isLittleEndian();

template <typename Scalar>
std::array<unsigned char, sizeof(Scalar)> 
	copyAsBigEndian(Scalar val, 
					typename std::enable_if<std::is_scalar<Scalar>::value>::type* = 0);

template <typename Scalar>
std::array<unsigned char, sizeof(Scalar)> 
	copyAsLittleEndian(Scalar val,
					   typename std::enable_if<std::is_scalar<Scalar>::value>::type* = 0);


#include "Endianess.inl"

#endif