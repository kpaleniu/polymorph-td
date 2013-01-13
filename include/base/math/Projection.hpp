/**
 * @file Projection.hpp
 */

#ifndef PROJECTION_HPP_
#define PROJECTION_HPP_

#include "math/types.hpp"
#include "math/Matrix.hpp"

#include <Eigen/Geometry>

#include <ostream>
#include <iomanip>
#include <array>

namespace math {

template<typename S, bool RowMajor>
class Projection;

}

template<typename S, bool RowMajor>
std::ostream& operator<<(std::ostream&, const math::Projection<S, RowMajor>&);


namespace math {

template<typename S, bool RowMajor = false>
class Projection : private Eigen::Transform<S, 3, Eigen::Projective, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>
{
public:
	friend std::ostream& operator<<<S, RowMajor>(std::ostream&, const Projection<S, RowMajor>&);

	typedef S radian_t;

	Projection(const Projection&) 				= default;
	Projection& operator=(const Projection&) 	= default;

	const S* data() const;

	Matrix<S, 3u, 1u, false> operator*(const Matrix<S, 3u, 1u, false>& vec3) const;
	Matrix<S, 4u, 1u, false> operator*(const Matrix<S, 4u, 1u, false>& vec4) const;

	/** @name Factories
	 * Public constructors.
	 */
	///@{
	static Projection<S, RowMajor> ortho(S left, S right, S bottom, S top, S near, S far);
	///@}

private:
	typedef Eigen::Transform<S, 3, Eigen::Projective, RowMajor ? Eigen::RowMajor : Eigen::ColMajor> EigenDerived;

	Projection(const EigenDerived& data);
};


// Implementation:

template<typename S, bool RowMajor>
inline Projection<S, RowMajor>::Projection(const EigenDerived& data)
:	EigenDerived(data)
{}

template<typename S, bool RowMajor>
inline const S* Projection<S, RowMajor>::data() const
{
	return EigenDerived::data();
}

template<typename S, bool RowMajor>
inline Matrix<S, 3u, 1u, false> Projection<S, RowMajor>::operator*(const Matrix<S, 3u, 1u, false>& vec3) const
{
	Eigen::Matrix<S, 4u, 1u, Eigen::ColMajor> vec4;
	vec4 << vec3(0,0), vec3(1,0), vec3(2,0), 1.0f;

	Eigen::Matrix<S, 4u, 1u, Eigen::ColMajor> resultVec4 = EigenDerived::operator*(vec4);
	Eigen::Matrix<S, 3u, 1u, Eigen::ColMajor> resultVec3;
	resultVec3 << resultVec4(0,0), resultVec4(1,0), resultVec4(2,0);

	return Matrix<S, 3u, 1u, false>(resultVec3);
}

template<typename S, bool RowMajor>
inline Matrix<S, 4u, 1u, false> Projection<S, RowMajor>::operator*(const Matrix<S, 4u, 1u, false>& vec4) const
{
	return Matrix<S, 4u, 1u, false>(EigenDerived::operator*(vec4.asEigen()));
}

template<typename S, bool RowMajor>
inline Projection<S, RowMajor> Projection<S, RowMajor>::ortho(S left, S right, S bottom, S top, S near_, S far_)
{
	S rightMleft = right - left;
	S rightPleft = right + left;
	S topMbottom = top - bottom;
	S topPbottom = top + bottom;
	S farMnear = far_ - near_;		// For some reason far - near causes error.
	S farPnear = far_ + near_;


	Eigen::Matrix<S, 4, 4, RowMajor ? Eigen::RowMajor : Eigen::ColMajor> mat;

	mat << 	S(2) / rightMleft, S(0), 			S(0), 				rightPleft / rightMleft,
			S(0),		S(2) / topMbottom,		S(0), 				topPbottom / topMbottom,
			S(0),		S(0),					S(-2) / farMnear,	farPnear / farMnear,
			S(0),		S(0),					S(0),				S(1);

	return Projection<S, RowMajor>(EigenDerived(mat));
}

}

template<typename S, bool RowMajor>
std::ostream& operator<<(std::ostream& out, const math::Projection<S, RowMajor>& proj)
{
	out << "Projection transformation " << (RowMajor ? "Row major" : "Column major") << std::endl;
	for (unsigned int row = 0; row < 4; ++row)
	{
		out << "|" << " ";
		for (unsigned int col = 0; col < 4; ++col)
			out << std::fixed
				<< std::showpoint
				<< std::setprecision(3)
				<< std::setw(8)
				<< proj(row, col)
				<< " ";
		out << "|" << std::endl;
	}

	return out;
}


#endif
