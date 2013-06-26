#ifndef PROJECTION_HPP_
#define PROJECTION_HPP_

#include "math/Matrix.hpp"

namespace math {

template <typename Arithmetic, bool RowMajor=false>
class Projection
{
public:
	const Arithmetic* data() const;

	Matrix<Arithmetic, 3u, 1u, RowMajor> operator*(
		const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& vec3) const;
	Matrix<Arithmetic, 4u, 1u, RowMajor> operator*(
		const MatrixMap<Arithmetic, 4u, 1u, RowMajor>& vec4) const;

	Projection<Arithmetic, RowMajor> inverse() const;

	Projection<Arithmetic, RowMajor>& 
		operator=(const Projection<Arithmetic, RowMajor>& other);

	static Projection<Arithmetic, RowMajor> ortho(
		Arithmetic left, Arithmetic right, 
		Arithmetic bottom, Arithmetic top, 
		Arithmetic near, Arithmetic far);

private:
	Projection(const Matrix<Arithmetic, 4u, 4u, RowMajor>& projMat,
			   const Matrix<Arithmetic, 4u, 4u, RowMajor>& invMat);

	Matrix<Arithmetic, 4u, 4u, RowMajor> _projMat;
	Matrix<Arithmetic, 4u, 4u, RowMajor> _invMat;
};

}

#include "math/Projection.inl"

#endif
