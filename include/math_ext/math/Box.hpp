#ifndef MATH_BOX_HPP_
#define MATH_BOX_HPP_

#include "math/Matrix.hpp"
#include "math/Transform.hpp"

namespace math {

template <typename Arithmetic, bool RowMajor=true>
class AxisAlignedBox
{
public:
	AxisAlignedBox(Arithmetic minX, Arithmetic minY, Arithmetic minZ,
				   Arithmetic maxX, Arithmetic maxY, Arithmetic maxZ);

	AxisAlignedBox(const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& c1,
				   const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& c2);

	// Returns true if inside or on edge:
	bool inside(Arithmetic x, Arithmetic y, Arithmetic z) const;
	bool inside(const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& p) const;
	//


	AxisAlignedBox<Arithmetic, RowMajor> 
		operator+(const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& p) const;
	AxisAlignedBox<Arithmetic, RowMajor>& 
		operator+=(const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& p);

	AxisAlignedBox<Arithmetic, RowMajor> 
		operator-(const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& p) const;
	AxisAlignedBox<Arithmetic, RowMajor>& 
		operator-=(const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& p);

private:
	Matrix<Arithmetic, 3u, 1u, RowMajor> _minP;
	Matrix<Arithmetic, 3u, 1u, RowMajor> _maxP;
};

}

#include "math/Box.inl"

#endif