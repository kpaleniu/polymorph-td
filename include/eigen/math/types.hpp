/**
 * @file types.hpp
 *
 */

#ifndef MATH_TYPES_HPP_
#define MATH_TYPES_HPP_

#include <Cpp11.hpp>

namespace math {

typedef float real_t;

#ifndef NO_CONSTEXPR

constexpr real_t PI = 3.141592;

constexpr real_t TWO_PI = PI * real_t(2);
constexpr real_t HALF_PI = PI / real_t(2);
constexpr real_t QUARTER_PI = PI / real_t(4);


constexpr real_t degToRad(real_t deg)
{ return deg * (PI / real_t(180)); }

constexpr real_t radToDeg(real_t rad)
{ return rad * (real_t(180) / PI); }

#else

#define PI			real_t(3.141592)

#define TWO_PI		real_t(PI * real_t(2))
#define HALF_PI		real_t(PI / real_t(2))
#define QUARTER_PI	real_t(PI / real_t(4))

#define degToRad(deg) ( deg * (PI / real_t(180)) )
#define radToDeg(rad) ( deg * (real_t(180) / PI) )

#endif

}


#endif /* MATH_TYPES_HPP_ */
