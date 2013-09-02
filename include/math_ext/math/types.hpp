/**
 * @file types.hpp
 *
 */

#ifndef MATH_TYPES_HPP_
#define MATH_TYPES_HPP_

#include <cmath>
#include <Cpp11.hpp>

#define PI			math::real_t(3.1415926535897932384626433832795)
#define TWO_PI		math::real_t(PI * math::real_t(2))
#define HALF_PI		math::real_t(PI / math::real_t(2))
#define QUARTER_PI	math::real_t(PI / math::real_t(4))


namespace math {

enum Dimension
{
	DYNAMIC = 0
};


typedef float real_t;
typedef real_t radian_t;

typedef unsigned int index_t;

template <typename Arithmetic>
Arithmetic sign(Arithmetic s)
{
	if (s >= 0)
		return 1;
	
	return -1;
}

inline real_t degToRad(real_t deg)
{
	return deg * (PI / real_t(180));
}

inline real_t radToDeg(real_t rad)
{
	return rad * (real_t(180) / PI);
}

template <typename Arithmetic>
inline Arithmetic square(Arithmetic val)
{
	return val * val;
}

}

#endif
