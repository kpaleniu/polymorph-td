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
inline Projection<S, RowMajor> Projection<S, RowMajor>::ortho(S left, S right, S bottom, S top, S near, S far)
{
	S rMl = right - left;
	S rPl = right + left;
	S tMb = top - bottom;
	S tPb = top + bottom;
	S fMn = far - near;
	S fPn = far + near;

	Eigen::Matrix<S, 4, 4, RowMajor ? Eigen::RowMajor : Eigen::ColMajor> mat;

	mat << 	S(2) / rMl, S(0), 			S(0), 			rPl / rMl,
			S(0),		S(2) / tMb,		S(0), 			tPb / tMb,
			S(0),		S(0),			S(-2) / fMn,	fPn / fMn,
			S(0),		S(0),			S(0),			S(1);

	return Projection<S, RowMajor>(EigenDerived(mat));
}

}

#endif
