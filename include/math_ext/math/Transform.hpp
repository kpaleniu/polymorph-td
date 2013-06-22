/**
 * @file Transform.hpp
 *
 * Contains some generic transformations.
 */

#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include "math/Matrix.hpp"

#include <Cpp11.hpp>

namespace math {

template <typename Arithmetic, bool RowMajor = false>
class Transform
{
public:
	typedef Arithmetic radian_t;

	Transform();

	Transform(const Transform<Arithmetic, RowMajor>& other);

	Transform<Arithmetic, RowMajor> inverse() const;

	void invert();

	void transform(MatrixMap<Arithmetic, 2u, 1u, RowMajor>& vec2) const;
	void transform(MatrixMap<Arithmetic, 3u, 1u, RowMajor>& vec3) const;
	void transform(MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>& vec) const;

	Matrix<Arithmetic, 2u, 1u, RowMajor> operator*(const MatrixMap<Arithmetic, 2u, 1u, RowMajor>& vec2) const;
	Matrix<Arithmetic, 3u, 1u, RowMajor> operator*(const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& vec3) const;

	Transform<Arithmetic, RowMajor> operator*(const Transform<Arithmetic, RowMajor>& other) const;
	Transform<Arithmetic, RowMajor>& operator*=(const Transform<Arithmetic, RowMajor>& other);

	Matrix<Arithmetic, 4u, 4u, RowMajor> asAffineMatrix() const;

	MatrixMap<Arithmetic, 3u, 1u, RowMajor>& translation();
	const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& translation() const;

	static const Transform<Arithmetic, RowMajor> IDENTITY;


	static Transform<Arithmetic, RowMajor> translate(
		const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& translation);
	
	static Transform<Arithmetic, RowMajor> translate(
		Arithmetic tx, Arithmetic ty, Arithmetic tz = 0);


	static Transform<Arithmetic, RowMajor> scale(Arithmetic scaling);
	
	static Transform<Arithmetic, RowMajor> scale(
		const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& scaling);

	static Transform<Arithmetic, RowMajor> scale(
		Arithmetic sx, Arithmetic sy, Arithmetic sz = 0);


	static Transform<Arithmetic, RowMajor> 
		eulerAngle(radian_t zAngle, radian_t yAngle = 0, radian_t xAngle = 0);

	
private:
	Matrix<Arithmetic, 3u, 3u, RowMajor> _topLeft;
	Matrix<Arithmetic, 3u, 1u, RowMajor> _translation;
};

}

#include "math/Transform.inl"

#endif