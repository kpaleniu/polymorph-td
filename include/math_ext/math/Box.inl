#include "math/Box.hpp"

#include <Debug.hpp>

#include <algorithm>

namespace math {

template <typename Arithmetic, bool RowMajor>
AxisAlignedBox<Arithmetic, RowMajor>::AxisAlignedBox(Arithmetic minX, Arithmetic minY, Arithmetic minZ,
													 Arithmetic maxX, Arithmetic maxY, Arithmetic maxZ)
:	_minP( {minX, minY, minZ} ), _maxP( {minX, minY, minZ} )
{
	ASSERT(minX <= maxX && minY <= maxY && minZ <= maxZ, "Bad arguments to Box constructor.");
}

template <typename Arithmetic, bool RowMajor>
AxisAlignedBox<Arithmetic, RowMajor>::AxisAlignedBox(const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& c1,
													 const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& c2)
:	_minP( {std::min(c1[0], c2[0]), std::min(c1[1], c2[1]), std::min(c1[2], c2[2])} ),
	_maxP( {std::max(c1[0], c2[0]), std::min(c1[1], c2[1]), std::max(c1[2], c2[2])} )
{
}

template <typename Arithmetic, bool RowMajor>
bool AxisAlignedBox<Arithmetic, RowMajor>::inside(Arithmetic x, Arithmetic y, Arithmetic z) const
{
	if (   (x < _minP[0] || x > _maxP[0])
		|| (y < _minP[1] || y > _maxP[1])
		|| (z < _minP[2] || z > _maxP[2]) )
	{
		return false;
	}

	return true;
}

template <typename Arithmetic, bool RowMajor>
bool AxisAlignedBox<Arithmetic, RowMajor>::inside(const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& p) const
{
	if (   (p[0] < _minP[0] || p[0] > _maxP[0])
		|| (p[1] < _minP[1] || p[1] > _maxP[1])
		|| (p[2] < _minP[2] || p[2] > _maxP[2]) )
	{
		return false;
	}

	return true;
}

template <typename Arithmetic, bool RowMajor>
AxisAlignedBox<Arithmetic, RowMajor> 
	AxisAlignedBox<Arithmetic, RowMajor>::operator+(const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& p) const
{
	AxisAlignedBox<Arithmetic, RowMajor> rBox(*this);

	rBox._minP += p;
	rBox._maxP += p;

	return rBox;
}

template <typename Arithmetic, bool RowMajor>
AxisAlignedBox<Arithmetic, RowMajor>& 
	AxisAlignedBox<Arithmetic, RowMajor>::operator+=(const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& p)
{
	_minP += p;
	_maxP += p;

	return *this;
}

template <typename Arithmetic, bool RowMajor>
AxisAlignedBox<Arithmetic, RowMajor> 
	AxisAlignedBox<Arithmetic, RowMajor>::operator-(const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& p) const
{
	AxisAlignedBox<Arithmetic, RowMajor> rBox(*this);

	rBox._minP -= p;
	rBox._maxP -= p;

	return rBox;
}

template <typename Arithmetic, bool RowMajor>
AxisAlignedBox<Arithmetic, RowMajor>& 
	AxisAlignedBox<Arithmetic, RowMajor>::operator-=(const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& p)
{
	_minP -= p;
	_maxP -= p;

	return *this;
}

}