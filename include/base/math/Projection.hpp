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

template<typename S, bool RowMajor = false>
class Projection : private Eigen::Transform<S, 3, Eigen::Projective, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>
{
public:
	//friend std::ostream& operator<<<S, RowMajor>(std::ostream&, const Projection<S, RowMajor>&);

	typedef S radian_t;

	Projection(const Projection&) 				= default;
	Projection& operator=(const Projection&) 	= default;

	const S* data() const;

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

#endif
