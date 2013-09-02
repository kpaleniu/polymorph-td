#include "math/Transform.hpp"

#include <Assert.hpp>

namespace math {


// Transform

template <typename Arithmetic, bool RowMajor>
const Transform<Arithmetic, RowMajor> Transform<Arithmetic, RowMajor>::IDENTITY = Transform<Arithmetic, RowMajor>();

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>::Transform()
:	_rotation(), _scale(), _translation()
{
	_scale[0] = Arithmetic(1);
	_scale[1] = Arithmetic(1);
	_scale[2] = Arithmetic(1);
}

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>::Transform(const Transform<Arithmetic, RowMajor>& other)
:	_rotation(other._rotation), 
	_scale(other._scale), 
	_translation(other._translation)
{
}

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>& 
	Transform<Arithmetic, RowMajor>::operator=(
			const Transform<Arithmetic, RowMajor>& other)
{
	_rotation = other._rotation;
	_scale = other._scale;
	_translation = other._translation;
	
	return *this;
}

/*
template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>
	Transform<Arithmetic, RowMajor>::inverse() const
{
	Transform<Arithmetic, RowMajor> rTrans(*this);

	rTrans.invert();

	return rTrans;
}

template <typename Arithmetic, bool RowMajor>
void Transform<Arithmetic, RowMajor>::invert()
{
	// FIXME Correct?

	_rotation.invert();
	
	_scale[0] = Arithmetic(1) / _scale[0];
	_scale[1] = Arithmetic(1) / _scale[1];
	_scale[2] = Arithmetic(1) / _scale[2];

	_translation = _translation * Arithmetic(-1);
}
*/

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>
	Transform<Arithmetic, RowMajor>::createTranslation(
			const MapVector3& translation)
{
	Transform<Arithmetic, RowMajor> rVal;

	rVal._translation = translation;

	return rVal;
}

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>
	Transform<Arithmetic, RowMajor>::createTranslation(
			Arithmetic tx, Arithmetic ty, Arithmetic tz)
{
	Transform<Arithmetic, RowMajor> rVal;

	rVal._translation(0, 0) = tx;
	rVal._translation(1, 0) = ty;
	rVal._translation(2, 0) = tz;

	return rVal;
}

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>
	Transform<Arithmetic, RowMajor>::createScaling(Arithmetic scaling)
{
	Transform<Arithmetic, RowMajor> rVal;

	rVal._scale[0] = 
		rVal._scale[1] =
			rVal._scale[2] = scaling;

	return rVal;
}

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>
	Transform<Arithmetic, RowMajor>::createScaling(
			const MapVector3& scaling)
{
	Transform<Arithmetic, RowMajor> rVal;

	rVal._scale = scaling;

	return rVal;
}

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>
	Transform<Arithmetic, RowMajor>::createScaling(
			Arithmetic sx, Arithmetic sy, Arithmetic sz)
{
	Transform<Arithmetic, RowMajor> rVal;

	rVal._scale[0] = sx;
	rVal._scale[1] = sy;
	rVal._scale[2] = sz;

	return rVal;
}

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>
	Transform<Arithmetic, RowMajor>::createRotation(
			const Quaternion<Arithmetic, RowMajor>& quat)
{
	Transform<Arithmetic, RowMajor> rVal;

	rVal._rotation = quat;

	return rVal;
}

template <typename Arithmetic, bool RowMajor>
Matrix<Arithmetic, 4u, 4u, RowMajor>
	Transform<Arithmetic, RowMajor>::asAffineMatrix() const
{
	Matrix<Arithmetic, 4u, 4u, RowMajor> rMat(Arithmetic(1));

	auto rotMat = _rotation.asAffineMatrix();

	for (index_t row = 0; row < 3; ++row)
		for (index_t col = 0; col< 3; ++col)
			rMat(row, col) = rotMat(row, col);

	for (index_t i = 0; i < 3; ++i)
		rMat(i, i) = _scale[i];

	for (index_t i = 0; i < 3; ++i)
		rMat(i, 3) = _translation[i];

	return rMat; // Last row is {0 0 0 1} due to constructor.
}

template <typename Arithmetic, bool RowMajor>
void Transform<Arithmetic, RowMajor>::transform(MapVector2& vec2) const
{
	Vector3 vec3 = 
	{
		vec2[0] * _scale[0], 
		vec2[1] * _scale[1],
		Arithmetic(0)
	};

	vec3 = _translation + _rotation * vec3;

	vec2[0] = vec3[0];
	vec2[1] = vec3[1];
}

template <typename Arithmetic, bool RowMajor>
void Transform<Arithmetic, RowMajor>::transform(MapVector3& vec3) const
{
	vec3[0] *= _scale[0];
	vec3[1] *= _scale[1];
	vec3[2] *= _scale[2];

	vec3 = _translation + _rotation * vec3;
}

template <typename Arithmetic, bool RowMajor>
void Transform<Arithmetic, RowMajor>::transform(MapVector& vec) const
{
	// Could be optimized.

	ASSERT(vec.rows() >= 2 && vec.rows() < 4, 
		   "Cannot transform vectors of this size.");

	Vector3 vec3 =
	{
		vec[0] * _scale[0], 
		vec[1] * _scale[1], 
		vec.rows() >= 3 ? vec[2] * _scale[2] : Arithmetic(0),
	};

	vec3 = _translation + _rotation * vec3;

	vec[0] = vec3[0];
	vec[1] = vec3[1];
	
	if (vec.rows() >= 3)
	{
		vec[2] = vec3[2];
		if (vec.rows() >= 4)
			vec[3] = vec3[3];
	}
}

template <typename Arithmetic, bool RowMajor>
Matrix<Arithmetic, 2u, 1u, RowMajor>
	Transform<Arithmetic, RowMajor>::operator*(const MapVector2& vec2) const
{
	Vector2 rVec;

	rVec = vec2;

	transform(rVec);

	return rVec;
}

template <typename Arithmetic, bool RowMajor>
Matrix<Arithmetic, 3u, 1u, RowMajor>
	Transform<Arithmetic, RowMajor>::operator*(const MapVector3& vec3) const
{
	Vector3 rVec;

	rVec = vec3;

	transform(rVec);

	return rVec;
}

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>
	Transform<Arithmetic, RowMajor>::operator*(const Transform<Arithmetic, RowMajor>& other) const
{
	Transform<Arithmetic, RowMajor> rTrans(*this);

	rTrans *= other;

	return rTrans;
}

template <typename Arithmetic, bool RowMajor>
Transform<Arithmetic, RowMajor>&
	Transform<Arithmetic, RowMajor>::operator*=(const Transform<Arithmetic, RowMajor>& other)
{
	_rotation = other._rotation * _rotation;

	for (index_t i = 0; i < 3; ++i)
		_scale[i] *= other._scale[i];

	_translation += other._translation;

	return *this;
}


template <typename Arithmetic, bool RowMajor>
typename Transform<Arithmetic, RowMajor>::Vector3& 
	Transform<Arithmetic, RowMajor>::translation()
{
	return _translation;
}

template <typename Arithmetic, bool RowMajor>
const typename Transform<Arithmetic, RowMajor>::Vector3 &
	Transform<Arithmetic, RowMajor>::translation() const
{
	return _translation;
}

template <typename Arithmetic, bool RowMajor>
typename Transform<Arithmetic, RowMajor>::Vector3 &
	Transform<Arithmetic, RowMajor>::scale()
{
	return _scale;
}

template <typename Arithmetic, bool RowMajor>
const typename Transform<Arithmetic, RowMajor>::Vector3 &
	Transform<Arithmetic, RowMajor>::scale() const
{
	return _scale;
}

template <typename Arithmetic, bool RowMajor>
Quaternion<Arithmetic, RowMajor>&
	Transform<Arithmetic, RowMajor>::rotation()
{
	return _rotation;
}

template <typename Arithmetic, bool RowMajor>
const Quaternion<Arithmetic, RowMajor>&
	Transform<Arithmetic, RowMajor>::rotation() const
{
	return _rotation;
}
}