#ifndef ENDIANESS_HPP_
#define ENDIANESS_HPP_

#include <array>
#include <type_traits>

inline bool isBigEndian();
inline bool isLittleEndian();

template <typename Scalar>
inline Scalar flippedEndianess(const Scalar& val);

template <typename Scalar>
inline void flipEndianess(Scalar& val);

inline void flipEndianess(void* data, std::size_t size);

#include "Endianess.inl"

#endif