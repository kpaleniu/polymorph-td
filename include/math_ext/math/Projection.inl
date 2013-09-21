#include "math/Projection.hpp"

namespace math {

template <typename Arithmetic, bool RowMajor>
Projection<Arithmetic, RowMajor>::Projection()
:	_projMat(Matrix<Arithmetic, 4u, 4u, RowMajor>::IDENTITY),
	_invMat(Matrix<Arithmetic, 4u, 4u, RowMajor>::IDENTITY)
{
}

template <typename Arithmetic, bool RowMajor>
Projection<Arithmetic, RowMajor>::Projection(
	const Matrix<Arithmetic, 4u, 4u, RowMajor>& projMat,
	const Matrix<Arithmetic, 4u, 4u, RowMajor>& invMat)
:	_projMat(projMat), _invMat(invMat)
{
}

template <typename Arithmetic, bool RowMajor>
const Arithmetic* Projection<Arithmetic, RowMajor>::data() const
{
	return _projMat.data();
}

template <typename Arithmetic, bool RowMajor>
Projection<Arithmetic, RowMajor>::operator const math::Matrix<Arithmetic, 4U, 4U, RowMajor>&()
{
	return _projMat;
}

template <typename Arithmetic, bool RowMajor>
Matrix<Arithmetic, 3u, 1u, RowMajor>
	Projection<Arithmetic, RowMajor>::operator*(
		const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& vec3) const
{
	Matrix<Arithmetic, 4u, 1u, RowMajor> vec4;
	vec4(0, 0) = vec3(0, 0);
	vec4(1, 0) = vec3(1, 0);
	vec4(2, 0) = vec3(2, 0);
	vec4(3, 0) = Arithmetic(1);

	Matrix<Arithmetic, 4u, 1u, RowMajor> tempV4 = _projMat * vec4;
	Matrix<Arithmetic, 3u, 1u, RowMajor> rVec3;
	
	rVec3(0, 0) = tempV4(0, 0);
	rVec3(1, 0) = tempV4(1, 0);
	rVec3(2, 0) = tempV4(2, 0);

	return rVec3;
}

template <typename Arithmetic, bool RowMajor>
Matrix<Arithmetic, 4u, 1u, RowMajor>
	Projection<Arithmetic, RowMajor>::operator*(
		const MatrixMap<Arithmetic, 4u, 1u, RowMajor>& vec4) const
{
	return _projMat * vec4;
}

template <typename Arithmetic, bool RowMajor>
Projection<Arithmetic, RowMajor>
	Projection<Arithmetic, RowMajor>::inverse() const
{
	return Projection(_invMat, _projMat);
}

template <typename Arithmetic, bool RowMajor>
Projection<Arithmetic, RowMajor>&
	Projection<Arithmetic, RowMajor>::operator=(const Projection<Arithmetic, RowMajor>& other)
{
	_projMat = other._projMat;
	_invMat = other._invMat;

	return *this;
}

template <typename Arithmetic, bool RowMajor>
Projection<Arithmetic, RowMajor>
	Projection<Arithmetic, RowMajor>::ortho(
		Arithmetic left, Arithmetic right, 
		Arithmetic bottom, Arithmetic top, 
		Arithmetic near_, Arithmetic far_)
{
	Arithmetic one = Arithmetic(1);
	Arithmetic two = Arithmetic(2);

	Arithmetic rightMleft = right - left;
	Arithmetic rightPleft = right + left;
	Arithmetic topMbottom = top - bottom;
	Arithmetic topPbottom = top + bottom;
	Arithmetic farMnear = far_ - near_;		// For some reason 'far - near' causes error.
	Arithmetic farPnear = far_ + near_;


	Matrix<Arithmetic, 4u, 4u, RowMajor> projMat;
	
	projMat(0, 0) = two / rightMleft;
	projMat(0, 3) = rightPleft / rightMleft;

	projMat(1, 1) = two / topMbottom;
	projMat(1, 3) = topPbottom / topMbottom;

	projMat(2, 2) = -two / farMnear;
	projMat(2, 3) = farPnear / farMnear;

	projMat(3, 3) = one;


	Matrix<Arithmetic, 4u, 4u, RowMajor> invMat;

	invMat(0, 0) = rightMleft / two;
	invMat(0, 3) = rightPleft / two;

	invMat(1, 1) = topMbottom / two;
	invMat(1, 3) = topPbottom / two;

	invMat(2, 2) = farMnear / (-two);
	invMat(2, 3) = farPnear / two;

	invMat(3, 3) = one;

	return Projection<Arithmetic, RowMajor>(projMat, invMat);
}

}