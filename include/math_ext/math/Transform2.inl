#include "math/Transform2.hpp"

namespace math {


template <typename Arithmetic, bool RowMajor>
const Transform2<Arithmetic, RowMajor> 
	Transform2<Arithmetic, RowMajor>::IDENTITY = Transform2<Arithmetic, RowMajor>();


template <typename Arithmetic, bool RowMajor>
Transform2<Arithmetic, RowMajor>::Transform2()
:	_translation({ 0, 0 }),
	_scale(1),
	_rotation(0)
{
}

template <typename Arithmetic, bool RowMajor>
void Transform2<Arithmetic, RowMajor>::transform(
	typename Transform2<Arithmetic, RowMajor>::MapVector2& vec2) const
{
	vec2 = *this * vec2;
}

template <typename Arithmetic, bool RowMajor>
void Transform2<Arithmetic, RowMajor>::transform(
	typename Transform2<Arithmetic, RowMajor>::MapVector& vec) const
{
	auto vec2 = *this * vec;

	vec[0] = vec2[0];
	vec[1] = vec2[1];
}

template <typename Arithmetic, bool RowMajor>
typename Transform2<Arithmetic, RowMajor>::Vector2
	Transform2<Arithmetic, RowMajor>::operator*(
		const typename Transform2<Arithmetic, RowMajor>::MapVector2& vec2) const
{
	auto vec3 = asAffineMatrix2() * Vector3({ vec2[0], vec2[1], 1 });
	return Vector2({ vec3[0], vec3[1] });
}

template <typename Arithmetic, bool RowMajor>
typename Transform2<Arithmetic, RowMajor>::Vector2
	Transform2<Arithmetic, RowMajor>::operator*(
		const typename Transform2<Arithmetic, RowMajor>::MapVector& vec) const
{
	auto vec3 = asAffineMatrix2() * Vector3({ vec[0], vec[1], 1 });
	return Vector2({ vec3[0], vec3[1] });
}

template <typename Arithmetic, bool RowMajor>
Transform2<Arithmetic, RowMajor> 
	Transform2<Arithmetic, RowMajor>::operator*(const Transform2& other) const
{
	Transform2<Arithmetic, RowMajor> rTrans;

	rTrans._rotation = _rotation + other._rotation;
	rTrans._scale = _scale * other._scale;

	Arithmetic
		sinThis = std::sin(_rotation),
		cosThis = std::cos(_rotation);

	rTrans._translation[0] =
		_scale *
			(cosThis * other._translation[0]
			- sinThis * other._translation[1]) + _translation[0];

	rTrans._translation[1] =
		_scale *
			(sinThis * other._translation[0]
			+ cosThis * other._translation[1]) + _translation[1];

	return rTrans;
}

template <typename Arithmetic, bool RowMajor>
Transform2<Arithmetic, RowMajor>
	Transform2<Arithmetic, RowMajor>::inverse() const
{
	Arithmetic
		sinMinRot = std::sin(-_rotation),
		cosMinRot = std::cos(-_rotation),
		invScale = Arithmetic(1) / _scale,
		x = _translation[0],
		y = _translation[1];


	Transform2<Arithmetic, RowMajor> rTrans;

	rTrans._rotation = -_rotation;
	rTrans._scale = invScale;

	rTrans._translation[0] = -invScale * (cosMinRot * x - sinMinRot * y);
	rTrans._translation[1] = -invScale * (sinMinRot * x + cosMinRot * y);

	return rTrans;
}

template <typename Arithmetic, bool RowMajor>
typename Transform2<Arithmetic, RowMajor>::Vector2&
	Transform2<Arithmetic, RowMajor>::translation()
{
	return _translation;
}
template <typename Arithmetic, bool RowMajor>
const typename Transform2<Arithmetic, RowMajor>::Vector2& 
	Transform2<Arithmetic, RowMajor>::translation() const
{
	return _translation;
}

template <typename Arithmetic, bool RowMajor>
Arithmetic& Transform2<Arithmetic, RowMajor>::scale()
{
	return _scale;
}
template <typename Arithmetic, bool RowMajor>
const Arithmetic& Transform2<Arithmetic, RowMajor>::scale() const
{
	return _scale;
}

template <typename Arithmetic, bool RowMajor>
radian_t& Transform2<Arithmetic, RowMajor>::rotation()
{
	return _rotation;
}
template <typename Arithmetic, bool RowMajor>
const radian_t& Transform2<Arithmetic, RowMajor>::rotation() const
{
	return _rotation;
}

template <typename Arithmetic, bool RowMajor>
Matrix<Arithmetic, 3u, 3u, RowMajor> 
	Transform2<Arithmetic, RowMajor>::asAffineMatrix2() const
{
	auto rMat(Matrix<Arithmetic, 3u, 3u, RowMajor>::IDENTITY);

	rMat(0, 0) = cos(_rotation) * _scale;
	rMat(0, 1) = -sin(_rotation) * _scale;
	rMat(0, 2) = _translation[0];

	rMat(1, 0) = sin(_rotation) * _scale;
	rMat(1, 1) = cos(_rotation) * _scale;
	rMat(1, 2) = _translation[1];

	return rMat;
}

template <typename Arithmetic, bool RowMajor>
Matrix<Arithmetic, 4u, 4u, RowMajor>
	Transform2<Arithmetic, RowMajor>::asAffineMatrix3() const
{
	auto rMat(Matrix<Arithmetic, 4u, 4u, RowMajor>::IDENTITY);

	rMat(0, 0) = cos(_rotation) * _scale;
	rMat(0, 1) = -sin(_rotation) * _scale;
	
	rMat(0, 3) = _translation[0];

	
	rMat(1, 0) = sin(_rotation) * _scale;
	rMat(1, 1) = cos(_rotation) * _scale;
	
	rMat(1, 3) = _translation[1];

	return rMat;
}

template <typename Arithmetic, bool RowMajor>
Transform2<Arithmetic, RowMajor> 
	Transform2<Arithmetic, RowMajor>::createTranslation(
		const typename Transform2<Arithmetic, RowMajor>::MapVector2& translation)
{
	Transform2<Arithmetic, RowMajor> rTrans;

	rTrans._translation = translation;
	
	return rTrans;
}

template <typename Arithmetic, bool RowMajor>
Transform2<Arithmetic, RowMajor>
	Transform2<Arithmetic, RowMajor>::createScaling(Arithmetic scale)
{
	Transform2<Arithmetic, RowMajor> rTrans;

	rTrans._scale = scale;

	return rTrans;
}

template <typename Arithmetic, bool RowMajor>
Transform2<Arithmetic, RowMajor>
	Transform2<Arithmetic, RowMajor>::createRotation(radian_t rotation)
{
	Transform2<Arithmetic, RowMajor> rTrans;

	rTrans._rotation = rotation;

	return rTrans;
}


}