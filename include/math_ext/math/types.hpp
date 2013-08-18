/**
 * @file types.hpp
 *
 */

#ifndef MATH_TYPES_HPP_
#define MATH_TYPES_HPP_

#include <Cpp11.hpp>

#define PI			math::real_t(3.141592)
#define TWO_PI		math::real_t(PI * math::real_t(2))
#define HALF_PI		math::real_t(PI / math::real_t(2))
#define QUARTER_PI	math::real_t(PI / math::real_t(4))


namespace math {

typedef float real_t;

inline real_t degToRad(real_t deg)
{
	return deg * (PI / real_t(180));
}

inline real_t radToDeg(real_t rad)
{
	return rad * (real_t(180) / PI);
}

}

#endif
