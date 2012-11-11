/**
 * @file Transform.hpp
 *
 */

#ifndef TRANSFORM2D_HPP_
#define TRANSFORM2D_HPP_

#include "math/types.hpp"

namespace math {

struct TransUST2D
{
	TransUST2D(real scaling_, real translation_);

	template<typename Vec2>
	Vec2 operator*(const Vec2& v) const;

	TransUST2D operator*(const TransUST2D& trans) const;

	real scaling;
	real translation;
};

//

template<typename Vec2>
inline Vec2 TransUST2D::operator*(const Vec2& v) const
{
	return Vec2(v[0] * scaling + translation,
	            v[1] * scaling + translation);
}


}


#endif
