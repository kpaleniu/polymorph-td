#include "math/Transform.hpp"

#include <Assert.hpp>

namespace math {


// Transform

template <typename Arithmetic, bool RowMajor>
const Transform<Arithmetic, RowMajor> Transform<Arithmetic, RowMajor>::IDENTITY = Transform<Arithmetic, RowMajor>();

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>::Transform()
:	_topLeft(Arithmetic(1)), _translation()
{
}

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>::Transform(const Transform<Arithmetic, RowMajor>& other)
:	_topLeft(other._topLeft), _translation(other._translation)
{
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

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor> 
	Transform<Arithmetic, RowMajor>::eulerAngle(radian_t zAngle, radian_t yAngle, radian_t xAngle)
{
	Transform<Arithmetic, RowMajor> rVal;

	Arithmetic 
		cosX = std::cos(xAngle),
		sinX = std::sin(xAngle),
		cosY = std::cos(yAngle),
		sinY = std::sin(yAngle),
		cosZ = std::cos(zAngle),
		sinZ = std::sin(zAngle);

	rVal._topLeft(0, 0) = cosY * cosZ;
	rVal._topLeft(1, 0) = -cosY * sinZ;
	rVal._topLeft(2, 0) = sinY;
	
	rVal._topLeft(0, 1) = cosX * sinZ + sinX * sinY * cosZ;
	rVal._topLeft(1, 1) = cosX * cosZ - sinX * sinY * sinZ;
	rVal._topLeft(2, 1) = -sinX * cosY;

	rVal._topLeft(0, 2) = sinX * sinZ - cosX * sinY * cosZ;
	rVal._topLeft(1, 2) = sinX * cosZ + cosX * sinY * sinZ;
	rVal._topLeft(2, 2) = cosX * cosY;

	return rVal;
}

template <typename Arithmetic, bool RowMajor>
void Transform<Arithmetic, RowMajor>::invert()
{
	_topLeft = inverse(_topLeft);
	_translation = ( (_topLeft * Arithmetic(-1)) * _translation );
}

template <typename Arithmetic, bool RowMajor>
Matrix<Arithmetic, 4u, 4u, RowMajor>
	Transform<Arithmetic, RowMajor>::asAffineMatrix() const
{
	Matrix<Arithmetic, 4u, 4u, RowMajor> rMat(Arithmetic(1));

	for (Matrix<Arithmetic, 3u, 3u, RowMajor>::index_t row = 0; row < 3; ++row)
		for (Matrix<Arithmetic, 3u, 3u, RowMajor>::index_t col = 0; col< 3; ++col)
			rMat(row, col) = _topLeft(row, col);

	for (Matrix<Arithmetic, 3u, 1u, RowMajor>::index_t row = 0; row < 3; ++row)
		rMat(row, 3u) = _translation[row];

	return rMat; // Last row is {0 0 0 1} due to constructor.
}

template <typename Arithmetic, bool RowMajor>
void Transform<Arithmetic, RowMajor>::transform(MatrixMap<Arithmetic, 2u, 1u, RowMajor>& vec2) const
{
	// Could be optimized.

	Matrix<Arithmetic, 4u, 1u, RowMajor> vec4 = 
	{
		vec2[0], 
		vec2[1], 
		Arithmetic(0), 
		Arithmetic(1)
	};

	vec4 = asAffineMatrix() * vec4;

	vec2[0] = vec4[0];
	vec2[1] = vec4[1];
}

template <typename Arithmetic, bool RowMajor>
void Transform<Arithmetic, RowMajor>::transform(MatrixMap<Arithmetic, 3u, 1u, RowMajor>& vec3) const
{
	// Could be optimized.

	Matrix<Arithmetic, 4u, 1u, RowMajor> vec4 = 
	{
		vec3[0], 
		vec3[1], 
		vec3[2], 
		Arithmetic(1)
	};

	vec4 = asAffineMatrix() * vec4;

	vec3[0] = vec4[0];
	vec3[1] = vec4[1];
	vec3[2] = vec4[2];
}

template <typename Arithmetic, bool RowMajor>
void Transform<Arithmetic, RowMajor>::transform(MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>& vec) const
{
	// Could be optimized.

	ASSERT(vec.rows() >= 2 && vec.rows() <= 4, "Cannot transform vectors of this size.");

	Matrix<Arithmetic, 4u, 1u, RowMajor> vec4 = 
	{
		vec[0], 
		vec[1], 
		vec.rows() >= 3 ? vec[2] : Arithmetic(0), 
		vec.rows() >= 4 ? vec[3] : Arithmetic(1),
	};

	vec4 = asAffineMatrix() * vec4;

	vec[0] = vec4[0];
	vec[1] = vec4[1];
	
	if (vec.rows() >= 3)
	{
		vec[2] = vec4[2];
		if (vec.rows() >= 4)
			vec[3] = vec4[3];
	}
}

template <typename Arithmetic, bool RowMajor>
Matrix<Arithmetic, 2u, 1u, RowMajor>
	Transform<Arithmetic, RowMajor>::operator*(const MatrixMap<Arithmetic, 2u, 1u, RowMajor>& vec2) const
{
	// Could be optimized.

	Matrix<Arithmetic, 4u, 1u, RowMajor> vec4 = 
	{
		vec2[0], 
		vec2[1], 
		Arithmetic(0), 
		Arithmetic(1)
	};

	vec4 = asAffineMatrix() * vec4;

	Matrix<Arithmetic, 2u, 1u, RowMajor> rVec;
	rVec[0] = vec4[0];
	rVec[1] = vec4[1];

	return rVec;
}

template <typename Arithmetic, bool RowMajor>
Matrix<Arithmetic, 3u, 1u, RowMajor>
	Transform<Arithmetic, RowMajor>::operator*(const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& vec3) const
{
	// Could be optimized.

	Matrix<Arithmetic, 4u, 1u, RowMajor> vec4 = 
	{
		vec3[0], 
		vec3[1], 
		vec3[2], 
		Arithmetic(1)
	};

	vec4 = asAffineMatrix() * vec4;

	Matrix<Arithmetic, 3u, 1u, RowMajor> rVec;
	rVec[0] = vec4[0];
	rVec[1] = vec4[1];
	rVec[2] = vec4[2];

	return rVec;
}

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>
	Transform<Arithmetic, RowMajor>::operator*(const Transform<Arithmetic, RowMajor>& other) const
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
			rTransform._topLeft(row, col) = matProduct(row, col);

	for (MatrixMap<Arithmetic, 3u, 1u, RowMajor>::index_t row = 0; row < 3; ++row)
		rTransform._translation(row, 0) = matProduct(row, 3);

	return rTransform;
}

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>&
	Transform<Arithmetic, RowMajor>::operator*=(const Transform<Arithmetic, RowMajor>& other)
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
			_topLeft(row, col) = matProduct(row, col);

	for (MatrixMap<Arithmetic, 3u, 1u, RowMajor>::index_t row = 0; row < 3; ++row)
		_translation[row] = matProduct(row, 3);

	return *this;
}

template <typename Arithmetic, bool RowMajor>
MatrixMap<Arithmetic, 3u, 1u, RowMajor>&
	Transform<Arithmetic, RowMajor>::translation()
{
	return _translation;
}

template <typename Arithmetic, bool RowMajor>
const MatrixMap<Arithmetic, 3u, 1u, RowMajor>&
	Transform<Arithmetic, RowMajor>::translation() const
{
	return _translation;
}

}