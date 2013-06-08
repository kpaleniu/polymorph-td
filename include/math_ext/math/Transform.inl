#include "math/Transform.hpp"

#include <Assert.hpp>

namespace math {


// Transform

template <typename Arithmetic, bool RowMajor>
const Transform<Arithmetic, RowMajor> Transform<Arithmetic, RowMajor>::IDENTITY = Transform<Arithmetic, RowMajor>();

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>::Transform()
:	TransformMap(), _topLeft(Arithmetic(1)), _translation()
{
	_mappedTopLeft = _topLeft;
	_mappedTranslation = _translation;
}

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>::Transform(const Transform<Arithmetic, RowMajor>& other)
:	TransformMap(), _topLeft(other._topLeft), _translation(other._translation)
{
	_mappedTopLeft = _topLeft;
	_mappedTranslation = _translation;
}

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>
	Transform<Arithmetic, RowMajor>::inverse() const
{
	Transform<Arithmetic, RowMajor> rTrans(*this);

	rTrans.invert();

	return rTrans;
}

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>
	Transform<Arithmetic, RowMajor>::translate(
		const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& translation)
{
	Transform<Arithmetic, RowMajor> rVal;

	rVal._translation = translation;

	return rVal;
}

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>
	Transform<Arithmetic, RowMajor>::translate(Arithmetic tx, Arithmetic ty, Arithmetic tz)
{
	Transform<Arithmetic, RowMajor> rVal;

	rVal._translation(0, 0) = tx;
	rVal._translation(1, 0) = ty;
	rVal._translation(2, 0) = tz;

	return rVal;
}

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>
	Transform<Arithmetic, RowMajor>::scale(Arithmetic scaling)
{
	Transform<Arithmetic, RowMajor> rVal;

	rVal._topLeft *= scaling;

	return rVal;
}

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>
	Transform<Arithmetic, RowMajor>::scale(
		const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& scaling)
{
	Transform<Arithmetic, RowMajor> rVal;

	for (MatrixMap<Arithmetic, 3u, 1u, RowMajor>::index_t i = 0; i < 3u; ++i)
		rVal._topLeft(i, i) = scaling(i, 0);

	return rVal;
}

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>
	Transform<Arithmetic, RowMajor>::scale(Arithmetic sx, Arithmetic sy, Arithmetic sz)
{
	Transform<Arithmetic, RowMajor> rVal;

	rVal._topLeft(0, 0) = sx;
	rVal._topLeft(1, 1) = sy;
	rVal._topLeft(2, 2) = sz;

	return rVal;
}


// TransformMap

template <typename Arithmetic, bool RowMajor>
TransformMap<Arithmetic, RowMajor>::TransformMap(
	const MatrixMap<Arithmetic, 3u, 3u, RowMajor>& topLeft,
	const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& translation)
:	_mappedTopLeft(topLeft), _mappedTranslation(translation)
{}

template <typename Arithmetic, bool RowMajor>
TransformMap<Arithmetic, RowMajor>::TransformMap()
:	_mappedTopLeft(), _mappedTranslation()
{}

template <typename Arithmetic, bool RowMajor>
void TransformMap<Arithmetic, RowMajor>::invert()
{
	_topLeft = inverse(_topLeft);
	_translation = ( (_topLeft * Arithmetic(-1)) * _translation );
}

template <typename Arithmetic, bool RowMajor>
Matrix<Arithmetic, 4u, 4u, RowMajor>
	TransformMap<Arithmetic, RowMajor>::asAffineMatrix() const
{
	Matrix<Arithmetic, 4u, 4u, RowMajor> rMat(Arithmetic(1));

	for (Matrix<Arithmetic, 3u, 3u, RowMajor>::index_t row = 0; row < 3; ++row)
		for (Matrix<Arithmetic, 3u, 3u, RowMajor>::index_t col = 0; col< 3; ++col)
			rMat(row, col) = _mappedTopLeft(row, col);

	for (Matrix<Arithmetic, 3u, 1u, RowMajor>::index_t row = 0; row < 3; ++row)
		rMat(row, 3u) = _mappedTranslation(row, 0);

	return rMat; // Last row is {0 0 0 1} due to constructor.
}

template <typename Arithmetic, bool RowMajor>
Matrix<Arithmetic, 2u, 1u, RowMajor>
	TransformMap<Arithmetic, RowMajor>::operator*(const MatrixMap<Arithmetic, 2u, 1u, RowMajor>& vec2) const
{
	// Could be optimized.

	Matrix<Arithmetic, 4u, 1u, RowMajor> vec4 = 
	{
		vec2[0], 
		vec2[1], 
		Arithmetic(0), 
		Arithmetic(1)
	};

	Matrix<Arithmetic, 4u, 1u, RowMajor> temp = asAffineMatrix() * vec4;

	Matrix<Arithmetic, 2u, 1u, RowMajor> rVec;
	for (Matrix<Arithmetic, 2u, 1u, RowMajor>::index_t row = 0; row < 2; ++row)
		rVec(row, 0) = temp(row, 0);

	return rVec;
}

template <typename Arithmetic, bool RowMajor>
Matrix<Arithmetic, 3u, 1u, RowMajor>
	TransformMap<Arithmetic, RowMajor>::operator*(const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& vec3) const
{
	// Could be optimized.

	Matrix<Arithmetic, 4u, 1u, RowMajor> vec4 = 
	{
		vec3[0], 
		vec3[1], 
		vec3[2], 
		Arithmetic(1)
	};

	Matrix<Arithmetic, 4u, 1u, RowMajor> temp = asAffineMatrix() * vec4;

	Matrix<Arithmetic, 3u, 1u, RowMajor> rVec;
	for (Matrix<Arithmetic, 3u, 1u, RowMajor>::index_t row = 0; row < 3; ++row)
		rVec(row, 0) = temp(row, 0);

	return rVec;
}

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>
	TransformMap<Arithmetic, RowMajor>::operator*(const TransformMap<Arithmetic, RowMajor>& other) const
{
	const auto matThis = asAffineMatrix();
	const auto matOther = other.asAffineMatrix();
	const auto matProduct = matThis * matOther;

	ASSERT( (matProduct(3, 0) == Arithmetic(0))
			&& (matProduct(3, 1) == Arithmetic(0))
			&& (matProduct(3, 2) == Arithmetic(0))
			&& (matProduct(3, 3) == Arithmetic(1)),
			"Transformation is no longer affine." );

	Transform<Arithmetic, RowMajor> rTransform;

	for (MatrixMap<Arithmetic, 3u, 3u, RowMajor>::index_t row = 0; row < 3; ++row)
		for (MatrixMap<Arithmetic, 3u, 3u, RowMajor>::index_t col = 0; col < 3; ++col)
			rTransform._mappedTopLeft(row, col) = matProduct(row, col);

	for (MatrixMap<Arithmetic, 3u, 1u, RowMajor>::index_t row = 0; row < 3; ++row)
		rTransform._mappedTranslation(row, 0) = matProduct(row, 3);

	return rTransform;
}

template <typename Arithmetic, bool RowMajor>
TransformMap<Arithmetic, RowMajor>&
	TransformMap<Arithmetic, RowMajor>::operator*=(const TransformMap<Arithmetic, RowMajor>& other)
{
	const auto matThis = asAffineMatrix();
	const auto matOther = other.asAffineMatrix();
	const auto matProduct = matThis * matOther;

	ASSERT( (matProduct(3, 0) == Arithmetic(0))
			&& (matProduct(3, 1) == Arithmetic(0))
			&& (matProduct(3, 2) == Arithmetic(0))
			&& (matProduct(3, 3) == Arithmetic(1)),
			"Transformation is no longer affine." );

	for (MatrixMap<Arithmetic, 3u, 3u, RowMajor>::index_t row = 0; row < 3; ++row)
		for (MatrixMap<Arithmetic, 3u, 3u, RowMajor>::index_t col = 0; col < 3; ++col)
			_mappedTopLeft(row, col) = matProduct(row, col);

	for (MatrixMap<Arithmetic, 3u, 1u, RowMajor>::index_t row = 0; row < 3; ++row)
		_mappedTranslation(row, 0) = matProduct(row, 3);

	return *this;
}

template <typename Arithmetic, bool RowMajor>
MatrixMap<Arithmetic, 3u, 1u, RowMajor>&
	TransformMap<Arithmetic, RowMajor>::translation()
{
	return _mappedTranslation;
}

template <typename Arithmetic, bool RowMajor>
const MatrixMap<Arithmetic, 3u, 1u, RowMajor>&
	TransformMap<Arithmetic, RowMajor>::translation() const
{
	return _mappedTranslation;
}

}