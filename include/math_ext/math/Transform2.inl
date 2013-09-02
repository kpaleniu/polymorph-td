#include "math/Transform2.hpp"

namespace math {


template <typename Arithmetic, bool RowMajor>
const Transform2<Arithmetic, RowMajor> 
	Transform2<Arithmetic, RowMajor>::IDENTITY = Transform2<Arithmetic, RowMajor>();


template <typename Arithmetic, bool RowMajor>
Transform2<Arithmetic, RowMajor>::Transform2()
:	_translation({ 0, 0 }),
	_scale({ 1, 1 }),
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
	return Transform2<Arithmetic, RowMajor>::
		createFromAffine(asAffineMatrix2() * other.asAffineMatrix2());
}

template <typename Arithmetic, bool RowMajor>
bool Transform2<Arithmetic, RowMajor>::operator==(
	const Transform2<Arithmetic, RowMajor>& other) const
{
	if (this == &other)
		return true;

	// Note: Scale-rotation-translation is ambigous,
	return asAffineMatrix2() == other.asAffineMatrix2();
}

template <typename Arithmetic, bool RowMajor>
bool Transform2<Arithmetic, RowMajor>::operator!=(
	const Transform2<Arithmetic, RowMajor>& other) const
{
	return !(*this == other);
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
typename Transform2<Arithmetic, RowMajor>::Vector2& 
	Transform2<Arithmetic, RowMajor>::scale()
{
	return _scale;
}
template <typename Arithmetic, bool RowMajor>
const typename Transform2<Arithmetic, RowMajor>::Vector2& 
	Transform2<Arithmetic, RowMajor>::scale() const
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

	rMat(0, 0) = cos(_rotation) * _scale[0];
	rMat(0, 1) = -sin(_rotation) * _scale[0];
	rMat(0, 2) = _translation[0];

	rMat(1, 0) = sin(_rotation) * _scale[1];
	rMat(1, 1) = cos(_rotation) * _scale[1];
	rMat(1, 2) = _translation[1];

	return rMat;
}


template <typename Arithmetic, bool RowMajor>
Transform2<Arithmetic, RowMajor> 
	Transform2<Arithmetic, RowMajor>::createTranslation(
		const typename Transform2<Arithmetic, RowMajor>::MapVector2& translation)
{
	Transform2 rTrans;

	rTrans._translation = translation;
	
	return rTrans;
}

template <typename Arithmetic, bool RowMajor>
Transform2<Arithmetic, RowMajor>
	Transform2<Arithmetic, RowMajor>::createScaling(
		const typename Transform2<Arithmetic, RowMajor>::MapVector2& scale)
{
	Transform2 rTrans;

	rTrans._scale = scale;

	return rTrans;
}

template <typename Arithmetic, bool RowMajor>
Transform2<Arithmetic, RowMajor>
	Transform2<Arithmetic, RowMajor>::createScaling(Arithmetic scale)
{
	Transform2 rTrans;

	rTrans._scale = { scale, scale };

	return rTrans;
}

template <typename Arithmetic, bool RowMajor>
Transform2<Arithmetic, RowMajor>
	Transform2<Arithmetic, RowMajor>::createRotation(radian_t rotation)
{
	Transform2 rTrans;

	rTrans._rotation = rotation;

	return rTrans;
}

template <typename Arithmetic, bool RowMajor>
Transform2<Arithmetic, RowMajor>
	Transform2<Arithmetic, RowMajor>::createFromAffine(
		const MatrixMap<Arithmetic, 3u, 3u, RowMajor>& mat)
{
	Transform2 rTrans;

	rTrans._translation = Vector2({ mat(0, 2), mat(1, 2) });

	rTrans._scale = Vector2(
	{
		sign(mat(0, 0)) * sqrt(square(mat(0, 0)) + square(mat(0, 1))),
		sign(mat(1, 1)) * sqrt(square(mat(1, 0)) + square(mat(1 ,1)))
	});

	rTrans._rotation = atan(-mat(0, 1) / mat(0, 0));

	return rTrans;
}

}