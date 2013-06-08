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

template <typename Arithmetic, bool RowMajor>
class TransformMap;

template <typename Arithmetic, bool RowMajor = false>
class Transform : public TransformMap<Arithmetic, RowMajor>
{
public:
	Transform();

	Transform(const Transform<Arithmetic, RowMajor>& other);

	Transform<Arithmetic, RowMajor> inverse() const;

	static const Transform<Arithmetic, RowMajor> IDENTITY;

	static Transform<Arithmetic, RowMajor> translate(
		const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& translation);
	
	static Transform<Arithmetic, RowMajor> translate(
		Arithmetic tx, Arithmetic ty, Arithmetic tz = 0);

	static Transform<Arithmetic, RowMajor> scale(Arithmetic scaling);
	
	static Transform<Arithmetic, RowMajor> scale(
		const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& scaling);

	static Transform<Arithmetic, RowMajor> scale(
		Arithmetic sx, Arithmetic sy, Arithmetic sz);

	// static Transform<S, RowMajor> rotateAxis(const Matrix<S, 3u, 1u, RM>& axis, radian_t rads);

private:
	Matrix<Arithmetic, 3u, 3u, RowMajor> _topLeft;
	Matrix<Arithmetic, 3u, 1u, RowMajor> _translation;
};

template <typename Arithmetic, bool RowMajor = false>
class TransformMap
{
public:
	TransformMap(const MatrixMap<Arithmetic, 3u, 3u, RowMajor>& topLeft,
				 const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& translation);

	TransformMap();

	void invert();

	Matrix<Arithmetic, 2u, 1u, RowMajor> operator*(const MatrixMap<Arithmetic, 2u, 1u, RowMajor>& vec2) const;
	Matrix<Arithmetic, 3u, 1u, RowMajor> operator*(const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& vec3) const;

	Transform<Arithmetic, RowMajor> operator*(const TransformMap<Arithmetic, RowMajor>& other) const;
	TransformMap<Arithmetic, RowMajor>& operator*=(const TransformMap<Arithmetic, RowMajor>& other);

	Matrix<Arithmetic, 4u, 4u, RowMajor> asAffineMatrix() const;

	MatrixMap<Arithmetic, 3u, 1u, RowMajor>& translation();
	const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& translation() const;

protected:
	MatrixMap<Arithmetic, 3u, 3u, RowMajor> _mappedTopLeft;
	MatrixMap<Arithmetic, 3u, 1u, RowMajor> _mappedTranslation;
};

}

#include "math/Transform.inl"

#endif