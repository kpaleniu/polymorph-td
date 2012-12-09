/**
 * @file types.hpp
 *
 */

#ifndef MATH_TYPES_HPP_
#define MATH_TYPES_HPP_

namespace math {

typedef float real_t;

constexpr real_t PI = 3.141592;

constexpr real_t TWO_PI = PI * real_t(2);
constexpr real_t HALF_PI = PI / real_t(2);
constexpr real_t QUARTER_PI = PI / real_t(4);


constexpr real_t degToRad(real_t deg)
{ return deg * (PI / real_t(180)); }

constexpr real_t radToDeg(real_t deg)
{ return deg * (real_t(180) / PI); }


}


#endif /* MATH_TYPES_HPP_ */
