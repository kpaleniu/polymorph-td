#ifndef ENDIANESS_HPP_
#define ENDIANESS_HPP_

#include <array>
#include <type_traits>

inline bool isBigEndian();
inline bool isLittleEndian();

template <typename Scalar>
Scalar flipEndianess(Scalar val);


#include "Endianess.inl"

#endif