/**
 * @file Transform.hpp
 *
 * Contains some generic transformations.
 */

#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include "math/Matrix.hpp"
#include "math/Quaternion.hpp"
#include "math/types.hpp"

#include <Cpp11.hpp>

namespace math {

template <typename Arithmetic, bool RowMajor = false>
class Transform
{
public:
	typedef Matrix<Arithmetic, 2u, 1u, RowMajor> Vector2;
	typedef Matrix<Arithmetic, 3u, 1u, RowMajor> Vector3;
	typedef MatrixMap<Arithmetic, 2u, 1u, RowMajor> MapVector2;
	typedef MatrixMap<Arithmetic, 3u, 1u, RowMajor> MapVector3;
	typedef MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor> MapVector;

public:
	Transform();
	Transform(const Transform<Arithmetic, RowMajor>& other);
	
	Transform<Arithmetic, RowMajor>& operator=(const Transform<Arithmetic, RowMajor>& other);

	/*
	Transform<Arithmetic, RowMajor> inverse() const;
	void invert();
	*/

	void transform(MapVector2& vec2) const;
	void transform(MapVector3& vec3) const;
	void transform(MapVector& vec) const;

	Vector2	operator*(const MapVector2& vec2) const;
	Vector3	operator*(const MapVector3& vec3) const;
	
	Transform<Arithmetic, RowMajor> 
		operator*(const Transform<Arithmetic, RowMajor>& other) const;
	
	Transform<Arithmetic, RowMajor>& 
		operator*=(const Transform<Arithmetic, RowMajor>& other);

	Matrix<Arithmetic, 4u, 4u, RowMajor> asAffineMatrix() const;


	Vector3&		translation();
	const Vector3&	translation() const;

	Vector3&		scale();
	const Vector3&	scale() const;

	Quaternion<Arithmetic, RowMajor>&		rotation();
	const Quaternion<Arithmetic, RowMajor>& rotation() const;


	static Transform<Arithmetic, RowMajor> createTranslation(
		const MapVector3& translation);
	
	static Transform<Arithmetic, RowMajor> createTranslation(
		Arithmetic tx, Arithmetic ty, Arithmetic tz = 0);


	static Transform<Arithmetic, RowMajor> createScaling(Arithmetic scaling);
	
	static Transform<Arithmetic, RowMajor> createScaling(
		const MapVector3& scaling);

	static Transform<Arithmetic, RowMajor> createScaling(
		Arithmetic sx, Arithmetic sy, Arithmetic sz = 0);


	static Transform<Arithmetic, RowMajor> 
		createRotation(const Quaternion<Arithmetic, RowMajor>& quat);


	static const Transform<Arithmetic, RowMajor> IDENTITY;

	
private:
	Quaternion<Arithmetic, RowMajor>     _rotation;
	Matrix<Arithmetic, 3u, 1u, RowMajor> _scale;
	Matrix<Arithmetic, 3u, 1u, RowMajor> _translation;
};

}

#include "math/Transform.inl"

#endif