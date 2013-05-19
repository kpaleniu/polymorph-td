#ifndef ENDIANESS_HPP_
#define ENDIANESS_HPP_

#include <array>
#include <type_traits>

inline bool isBigEndian();
inline bool isLittleEndian();

template <typename Scalar>
std::array<unsigned char, sizeof(Scalar)> 
	copyAsBigEndian(Scalar val);

template <typename Scalar>
std::array<unsigned char, sizeof(Scalar)> 
	copyAsLittleEndian(Scalar val);


#include "Endianess.inl"

#endif