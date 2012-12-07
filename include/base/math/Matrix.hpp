

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

	S* data();
	const S* data() const;

	S& operator()(index_t row, index_t col);
	const S& operator()(index_t row, index_t col) const;
};

}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
std::ostream& operator<<(std::ostream& out, const math::Matrix<S, Rows, Cols, RowMajor>& mat);

namespace math {

typedef Matrix<real_t, 3, 3> Matrix3x3_r;
typedef Matrix<real_t, 4, 4> Matrix4x4_r;


// Implementation:

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
	memcpy(Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>
				::data(), data.data(), Rows * Cols);
}

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

}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline std::ostream& operator <<(std::ostream& out, const math::Matrix<S, Rows, Cols, RowMajor>& mat)
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
