
#include "math/Quaternion.hpp"

namespace math {

template <typename Arithmetic, bool RowMajor>
Quaternion<Arithmetic, RowMajor> Quaternion<Arithmetic, RowMajor>::IDENTITY
	= Quaternion<Arithmetic, RowMajor>();

template <typename Arithmetic, bool RowMajor>
Quaternion<Arithmetic, RowMajor>::Quaternion()
:	_real(1), _imag()
{
}

template <typename Arithmetic, bool RowMajor>
Quaternion<Arithmetic, RowMajor>::Quaternion(const Quaternion<Arithmetic, RowMajor>& other)
:	_real(other._real), _imag(other._imag)
{
	//ASSERT(norm() == Arithmetic(1), "Ctor Quaternion isn't normalized.");
}

template <typename Arithmetic, bool RowMajor>
Quaternion<Arithmetic, RowMajor>& Quaternion<Arithmetic, RowMajor>::operator=(
	const Quaternion<Arithmetic, RowMajor>& other)
{
	_real = other._real;
	_imag = other._imag;

	//ASSERT(norm() == Arithmetic(1), "Ctor Quaternion isn't normalized.");

	return *this;
}


template <typename Arithmetic, bool RowMajor>
Quaternion<Arithmetic, RowMajor>
	Quaternion<Arithmetic, RowMajor>::conjugate() const
{
	Quaternion<Arithmetic, RowMajor> rQuat(*this);

	rQuat._imag *= Arithmetic(-1);

	return rQuat;
}


template <typename Arithmetic, bool RowMajor>
Quaternion<Arithmetic, RowMajor>
	Quaternion<Arithmetic, RowMajor>::operator*(
			const Quaternion<Arithmetic, RowMajor>& other) const
{
	Quaternion<Arithmetic, RowMajor> rQuat;

	rQuat._real = _real * other._real - _imag * other._imag;
	rQuat._imag = crossProduct(_imag, other._imag) 
				  + other._imag * _real 
				  + other._imag * other._real;

	// ASSERT(rQuat.norm() == Arithmetic(1), "Ctor Quaternion isn't normalized.");

	return rQuat;
}

template <typename Arithmetic, bool RowMajor>
Matrix<Arithmetic, 3u, 1u, RowMajor>
	Quaternion<Arithmetic, RowMajor>::operator*(
			const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& vec3) const
{
	Arithmetic
		w = _real,
		two = Arithmetic(2);

	return vec3 + crossProduct(_imag * two, crossProduct(_imag, vec3) + vec3 * w);
}

template <typename Arithmetic, bool RowMajor>
Matrix<Arithmetic, 4u, 4u, RowMajor> Quaternion<Arithmetic, RowMajor>::
	asAffineMatrix() const
{
	auto rMat = Matrix<Arithmetic, 4u, 4u, RowMajor>::IDENTITY;

	Arithmetic
		w = _real,
		x = _imag[0],
		y = _imag[1],
		z = _imag[2],
		one = Arithmetic(1),
		two = Arithmetic(2);

	rMat(0, 0) = one - two * ( square(y) + square(z) );
	rMat(0, 1) = two * (y * z + w * x);
	rMat(0, 2) = two * (x * z - w * y);

	rMat(1, 0) = two * (x * y - w * z);
	rMat(1, 1) = one - two * ( square(x) + square(z) );
	rMat(1, 2) = two * (y * z - w * x);

	rMat(2, 0) = two * (x * z + w * y);
	rMat(2, 1) = two * (y * z - w * x);
	rMat(2, 2) = one - two * ( square(x) + square(y) );

	return rMat;
}

template <typename Arithmetic, bool RowMajor>
Quaternion<Arithmetic, RowMajor>
	Quaternion<Arithmetic, RowMajor>::angleAxis(
			radian_t angle, const MapVector3& axis)
{
	radian_t halfAngle = angle * 0.5f;

	Quaternion<Arithmetic, RowMajor> rQuat;
	rQuat._real = std::cos(halfAngle);
	rQuat._imag = axis * std::sin(halfAngle);

	return rQuat;
}

}