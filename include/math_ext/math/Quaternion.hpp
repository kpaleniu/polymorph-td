#ifndef MATH_QUATERNION_HPP_
#define MATH_QUATERNION_HPP_

#include "math/Matrix.hpp"
#include "math/types.hpp"

namespace math {

/**
 * Normalized Quaternion class.
 */
template <typename Arithmetic, bool RowMajor = false>
class Quaternion
{
public:
	typedef Matrix<Arithmetic, 3u, 1u, RowMajor> Vector2;
	typedef Matrix<Arithmetic, 3u, 1u, RowMajor> Vector3;
	typedef MatrixMap<Arithmetic, 3u, 1u, RowMajor> MapVector2;
	typedef MatrixMap<Arithmetic, 3u, 1u, RowMajor> MapVector3;
	typedef MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor> MapVector;

public:
	Quaternion();
	Quaternion(const Quaternion<Arithmetic, RowMajor>& other);

	Quaternion<Arithmetic, RowMajor>& operator=(const Quaternion<Arithmetic, RowMajor>& other);

	Quaternion<Arithmetic, RowMajor> conjugate() const;
	


	Quaternion<Arithmetic, RowMajor> 
		operator*(const Quaternion<Arithmetic, RowMajor>& other) const;

	Vector3	operator*(const MapVector3& vec3) const;

	Matrix<Arithmetic, 4u, 4u, RowMajor> asAffineMatrix() const;

	static Quaternion<Arithmetic, RowMajor>
		angleAxis(radian_t angle, const MapVector3& axis);

	static Quaternion<Arithmetic, RowMajor> IDENTITY;

private:

#ifdef _DEBUG
	//Arithmetic norm() const;
#endif

	Arithmetic _real;
	Vector3 _imag;
};


}

#include "math/Quaternion.inl"

#endif