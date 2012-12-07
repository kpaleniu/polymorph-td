

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "math/types.hpp"

#include <Eigen/Dense>

#include <ostream>
#include <array>
#include <cstring>

namespace math {

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor=true>
class Matrix : private Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>
{
public:
	typedef unsigned int index_t;

	Matrix();
	Matrix(S diagonal);
	Matrix(const std::array<S, Rows * Cols>& data);
	Matrix(const Matrix<S, Rows, Cols, RowMajor>& mat);

	S* data();
	const S* data() const;

	S& operator()(index_t row, index_t col);
	const S& operator()(index_t row, index_t col) const;

	Matrix<S, Rows, Cols, RowMajor> operator*(S scalar) const;
	Matrix<S, Rows, Cols, RowMajor> operator/(S scalar) const;
	Matrix<S, Rows, Cols, RowMajor> operator*=(S scalar);
	Matrix<S, Rows, Cols, RowMajor> operator/=(S scalar);

	template<unsigned int N, bool RM>
	Matrix<S, Rows, N, RM> operator*(const Matrix<S, Cols, N, RM>& other) const;

private:
	Matrix(const Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>& mat);

	// Yes this is legal C++11.
	template<typename _S, unsigned int _Rows, unsigned int _Cols, bool _RowMajor>
	friend class Matrix;
};

}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
std::ostream& operator<<(std::ostream& out, const math::Matrix<S, Rows, Cols, RowMajor>& mat);

namespace math {

typedef Matrix<real_t, 3, 3> Matrix3x3_r;
typedef Matrix<real_t, 4, 4> Matrix4x4_r;

typedef Matrix<real_t, 2, 1, false> Vector2_r;
typedef Matrix<real_t, 3, 1, false> Vector3_r;
typedef Matrix<real_t, 4, 1, false> Vector4_r;

// Implementation:

// Constructors	START
template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<S, Rows, Cols, RowMajor>::Matrix()
:	Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>()
{}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<S, Rows, Cols, RowMajor>::Matrix(S diagonal)
:	Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>()
{
	for (index_t row = 0; row < Rows; ++row)
		for (index_t col = 0; col < Cols; ++col)
			Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>
				::operator()(row, col) = (row == col ? S(diagonal) : S(0));
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<S, Rows, Cols, RowMajor>::Matrix(const std::array<S, Rows * Cols>& data)
:	Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>()
{
	// Could be done with memcpy?
	for (index_t row = 0; row < Rows; ++row)
	{
		for (index_t col = 0; col < Cols; ++col)
		{
			Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>
											::operator()(row, col) = data[(RowMajor ? row : col) * Cols
											                              + (RowMajor ? col : row)];
		}
	}
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<S, Rows, Cols, RowMajor>::Matrix(const Matrix<S, Rows, Cols, RowMajor>& mat)
:	Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>(mat)
{}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<S, Rows, Cols, RowMajor>::Matrix(
		const Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>& mat)
:	Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>(mat)
{}
// Constructors	END

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
S* Matrix<S, Rows, Cols, RowMajor>::data()
{
	return Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>
			::data();
}
template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
const S* Matrix<S, Rows, Cols, RowMajor>::data() const
{
	return Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>
			::data();
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
S& Matrix<S, Rows, Cols, RowMajor>::operator()(index_t row, index_t col)
{
	return Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>
			::operator()(row, col);
}
template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
const S& Matrix<S, Rows, Cols, RowMajor>::operator()(index_t row, index_t col) const
{
	return Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>
			::operator()(row, col);
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<S, Rows, Cols, RowMajor> Matrix<S, Rows, Cols, RowMajor>::operator*(S scalar) const
{
	return Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>
			::operator*(scalar);
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<S, Rows, Cols, RowMajor> Matrix<S, Rows, Cols, RowMajor>::operator/(S scalar) const
{
	return Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>
			::operator/(scalar);
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<S, Rows, Cols, RowMajor> Matrix<S, Rows, Cols, RowMajor>::operator*=(S scalar)
{
	Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>
		::operator*=(scalar);
	return *this;
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<S, Rows, Cols, RowMajor> Matrix<S, Rows, Cols, RowMajor>::operator/=(S scalar)
{
	Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>
		::operator/=(scalar);
	return *this;
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
template<unsigned int N, bool RM>
Matrix<S, Rows, N, RM> Matrix<S, Rows, Cols, RowMajor>
	::operator*(const Matrix<S, Cols, N, RM>& other) const
{
	return Matrix<S, Rows, N, RM>(Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>
											::operator*(other));
}

}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline std::ostream& operator<<(std::ostream& out, const math::Matrix<S, Rows, Cols, RowMajor>& mat)
{
	out << "Matrix" << Rows << "x" << Cols << " " << (RowMajor ? "Row major" : "Column major") << std::endl;

	for (typename math::Matrix<S, Rows, Cols, RowMajor>::index_t col = 0; col < Cols; ++col)
	{
		out << "|" << " ";
		for (typename math::Matrix<S, Rows, Cols, RowMajor>::index_t row = 0; row < Rows; ++row)
				out << mat(row, col) << " ";
		out << "|" << std::endl;
	}

	return out;
}


#endif
