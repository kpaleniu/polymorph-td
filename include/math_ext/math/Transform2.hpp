#ifndef MATH_TRANSFORM2_HPP_
#define MATH_TRANSFORM2_HPP_

#include "math/Matrix.hpp"
#include "math/types.hpp"

namespace math {

/**
 * 2D transformation class.
 */
template <typename Arithmetic, bool RowMajor = false>
class Transform2
{
public:
	typedef Matrix<Arithmetic, 2u, 1u, RowMajor> Vector2;
	typedef Matrix<Arithmetic, 3u, 1u, RowMajor> Vector3;
	typedef MatrixMap<Arithmetic, 2u, 1u, RowMajor> MapVector2;
	typedef MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor> MapVector;

public:
	Transform2();

	void transform(MapVector2& vec2) const;
	void transform(MapVector& vec) const;

	Vector2 operator*(const MapVector2& vec2) const;
	Vector2 operator*(const MapVector& vec) const;

	Transform2 operator*(const Transform2& other) const;

	Vector2&			translation();
	const Vector2&		translation() const;

	Arithmetic&			scale();
	const Arithmetic&	scale() const;

	radian_t&			rotation();
	const radian_t&		rotation() const;

	Matrix<Arithmetic, 3u, 3u, RowMajor> asAffineMatrix2() const;


	static Transform2<Arithmetic, RowMajor> createTranslation(
		const MapVector2& translation);

	static Transform2<Arithmetic, RowMajor> createScaling(
		Arithmetic uniformScale);

	static Transform2<Arithmetic, RowMajor> createRotation(
		radian_t rotation);

	static const Transform2<Arithmetic, RowMajor> IDENTITY;


private:
	Vector2		_translation;
	Arithmetic	_scale;
	radian_t	_rotation;
};


}

#include "math/Transform2.inl"

#endif