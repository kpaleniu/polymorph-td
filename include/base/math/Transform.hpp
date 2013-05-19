/**
 * @file Transform.hpp
 *
 * Contains some generic transformations.
 */

#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include "math/types.hpp"
#include "math/Matrix.hpp"

#include <Cpp11.hpp>

#include <Eigen/Geometry>

#include <ostream>
#include <iomanip>
#include <array>

namespace math {

template<typename S, bool RowMajor>
class Transform;

}

template<typename S, bool RowMajor>
std::ostream& operator<<(std::ostream&, const math::Transform<S, RowMajor>&);

namespace math {

// NOTE Consider replacing Eigen::Affine with Eigen::AffineCompact.
// 		Then also change the typedef EigenDerived.

template<typename S, bool RowMajor = false>
class Transform : private Eigen::Transform<S, 3, Eigen::Affine, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>
{
public:
#ifndef NO_TEMPLATE_FRIENDS
	friend std::ostream& operator<< <S, RowMajor> (std::ostream&, const Transform<S, RowMajor>&);
#endif

	typedef S radian_t;

	Matrix<S, 3u, 1u, false> operator*(const Matrix<S, 3u, 1u, false>& vec3) const;
	Transform<S, RowMajor> operator*(const Transform<S, RowMajor>& other) const;
	Transform<S, RowMajor>& operator*=(const Transform<S, RowMajor>& other);

	const S* data() const;

	Transform<S, RowMajor> inverse() const;

	/** @name Factories
	 * Public constructors.
	 */
	///@{
	static Transform<S, RowMajor> identity();
	template<bool RM>
	static Transform<S, RowMajor> translate(const Matrix<S, 3u, 1u, RM>& translation);
	static Transform<S, RowMajor> scale(S scaling);
	template<bool RM>
	static Transform<S, RowMajor> rotateAxis(const Matrix<S, 3u, 1u, RM>& axis, radian_t rads);
	///@}

private:
	typedef Eigen::Transform<S, 3, Eigen::Affine, RowMajor ? Eigen::RowMajor : Eigen::ColMajor> EigenDerived;

	Transform(const EigenDerived& data)
	:	EigenDerived(data)
	{}

#ifdef NO_TEMPLATE_FRIENDS
public:
#endif

	EigenDerived& asEigen()
	{ return static_cast<EigenDerived&>(*this); }

	const EigenDerived& asEigen() const
	{ return static_cast<const EigenDerived&>(*this); }
};

// Implementation:
/*
template<typename S, bool RowMajor>
inline Transform<S, RowMajor>::Transform(const Transform::EigenDerived& data)
:	Transform::EigenDerived(data)
{}
*/
template<typename S, bool RowMajor>
inline Matrix<S, 3u, 1u, false> Transform<S, RowMajor>::operator*(const Matrix<S, 3u, 1u, false>& vec3) const
{
	return Matrix<S, 3u, 1u, false>(EigenDerived::operator*(vec3.asEigen()));
}

template<typename S, bool RowMajor>
inline Transform<S, RowMajor> Transform<S, RowMajor>::operator*(const Transform<S, RowMajor>& other) const
{
	return Transform<S, RowMajor>(EigenDerived::operator*(other));
}

template<typename S, bool RowMajor>
inline Transform<S, RowMajor>& Transform<S, RowMajor>::operator*=(const Transform<S, RowMajor>& other)
{
	EigenDerived::operator*=(other);
	return *this;
}

template<typename S, bool RowMajor>
inline const S* Transform<S, RowMajor>::data() const
{
	return EigenDerived::data();
}

template<typename S, bool RowMajor>
inline Transform<S, RowMajor> Transform<S, RowMajor>::inverse() const
{
	return Transform<S, RowMajor>(EigenDerived::inverse());
}

template<typename S, bool RowMajor>
inline Transform<S, RowMajor> Transform<S, RowMajor>::identity()
{
	EigenDerived eigTransf;
	eigTransf.setIdentity();

	return Transform<S, RowMajor>(eigTransf);
}

template<typename S, bool RowMajor>
template<bool RM>
inline Transform<S, RowMajor> Transform<S, RowMajor>
	::translate(const Matrix<S, 3, 1, RM>& translation)
{
	EigenDerived eigTransf;
	eigTransf = Eigen::Translation<S, 3>(translation.asEigen());
	return Transform<S, RowMajor>(eigTransf);
}

template<typename S, bool RowMajor>
inline Transform<S, RowMajor> Transform<S, RowMajor>
	::scale(S scaling)
{
	EigenDerived eigTransf;
	eigTransf = Eigen::Scaling(scaling);
	return Transform<S, RowMajor>(eigTransf);
}

template<typename S, bool RowMajor>
template<bool RM>
inline Transform<S, RowMajor> Transform<S, RowMajor>
	::rotateAxis(const Matrix<S, 3, 1, RM>& axis, radian_t rads)
{
	EigenDerived eigTransf;
	eigTransf = Eigen::AngleAxis<S>(rads, axis.asEigen());
	return Transform<S, RowMajor>(eigTransf);
}


}

template<typename S, bool RowMajor>
std::ostream& operator<<(std::ostream& out, const math::Transform<S, RowMajor>& trans)
{
	out << "Affine transformation " << (RowMajor ? "Row major" : "Column major") << std::endl;
	auto affinePart = trans.asEigen().affine();
	for (unsigned int row = 0; row < 3; ++row)
	{
		out << "|" << " ";
		for (unsigned int col = 0; col < 4; ++col)
			out << std::fixed
				<< std::showpoint
				<< std::setprecision(3)
				<< std::setw(8)
				<< affinePart(row, col)
				<< " ";
		out << "|" << std::endl;
	}

	return out;
}


#endif
