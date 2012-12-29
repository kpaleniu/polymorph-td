#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "math/types.hpp"

#include <Eigen/Dense>

#include <ostream>
#include <iomanip>
#include <array>

namespace math {

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
class MatrixMap;

/**
 * Class for generic matrix.
 */
template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor=false>
class Matrix : private Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>
{
public:
	/**
	 * Type used for indexing.
	 */
	typedef unsigned int index_t;

	/**
	 * Empty constructor.
	 *
	 * Elements are un-initialized.
	 */
	Matrix();
	/**
	 * Diagonal constructor.
	 *
	 * All elements on the diagonal (ROW == COL) are the specified value,
	 * the rest are zero.
	 *
	 * @param diagonal	Value to set on diagonal.
	 */
	Matrix(S diagonal);
	/**
	 * Copy constructor.
	 *
	 * Copies the data in the array to the matrix.
	 * The parameter is assumed to be in Row-major order.
	 *
	 * TODO Add possibility to specify element order of parameter.
	 *
	 * @param data	Data buffer to copy.
	 */
	Matrix(const std::array<S, Rows * Cols>& data);
	/**
	 * Copy constructor.
	 *
	 * @param mat	Matrix to copy.
	 */
	Matrix(const Matrix<S, Rows, Cols, RowMajor>& mat);


	/** @name Element access
	 * Access to elements.
	 */
	///@{
	S* data();
	const S* data() const;

	S& operator()(index_t row, index_t col);
	const S& operator()(index_t row, index_t col) const;
	///@}


	/** @name Binary operators
	 * Vector space operators.
	 */
	///@{
	Matrix<S, Rows, Cols, RowMajor> operator*(S scalar) const;
	Matrix<S, Rows, Cols, RowMajor> operator/(S scalar) const;

	template<unsigned int N, bool RM>
	Matrix<S, Rows, N, RM> operator*(const Matrix<S, Cols, N, RM>& other) const;
	template<unsigned int N, bool RM>
	Matrix<S, Rows, N, RM> operator*(const MatrixMap<S, Cols, N, RM>& other) const;

	Matrix<S, Rows, Cols, RowMajor> operator*=(S scalar);
	Matrix<S, Rows, Cols, RowMajor> operator/=(S scalar);
	///@}

public:
	// Eigen implementation specific:

	typedef Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor> EigenDerived;
	EigenDerived& asEigen()
	{ return *this; }
	const EigenDerived& asEigen() const
	{ return *this; }

	Matrix(const EigenDerived& mat);

private:

	template<typename _S, unsigned int _Rows, unsigned int _Cols, bool _RowMajor>
	friend class Matrix;
	template<typename _S, unsigned int _Rows, unsigned int _Cols, bool _RowMajor>
	friend class MatrixMap;
};


template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor=false>
class MatrixMap : private Eigen::Map<Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>>
{
public:
	/**
	 * Type used for indexing.
	 */
	typedef unsigned int index_t;

	/**
	 * Constructor.
	 *
	 * TODO Add possibility to specify element order of parameter.
	 *
	 * @param data	Row-major ordered data to map.
	 */
	MatrixMap(S* data);

	/** @name Element access
	 * Access to elements.
	 */
	///@{
	S* data();
	const S* data() const;

	S& operator()(index_t row, index_t col);
	const S& operator()(index_t row, index_t col) const;
	///@}

	/** @name Binary operators
	 * Vector space operators.
	 */
	///@{
	Matrix<S, Rows, Cols, RowMajor> operator*(S scalar) const;
	Matrix<S, Rows, Cols, RowMajor> operator/(S scalar) const;
	MatrixMap<S, Rows, Cols, RowMajor> operator*=(S scalar);
	MatrixMap<S, Rows, Cols, RowMajor> operator/=(S scalar);

	template<unsigned int N, bool RM>
	Matrix<S, Rows, N, RM> operator*(const Matrix<S, Cols, N, RM>& other) const;
	template<unsigned int N, bool RM>
	Matrix<S, Rows, N, RM> operator*(const MatrixMap<S, Cols, N, RM>& other) const;
	///@}

public:
	// Eigen implementation specific:

	typedef Eigen::Map<Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>> EigenDerived;
	EigenDerived& asEigen()
	{ return *this; }
	const EigenDerived& asEigen() const
	{ return *this; }

};

}

/** @name Printing
 * Printers for matrices.
 */
///@{
template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
std::ostream& operator<<(std::ostream& out, const math::Matrix<S, Rows, Cols, RowMajor>& mat);

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline std::ostream& operator<<(std::ostream& out, const math::MatrixMap<S, Rows, Cols, RowMajor>& mat);
///@}

namespace math {

// Common types:

typedef Matrix<real_t, 3u, 3u> Matrix3x3_r;
typedef Matrix<real_t, 4u, 4u> Matrix4x4_r;

typedef Matrix<real_t, 2u, 1u, false> Vector2_r;
typedef Matrix<real_t, 3u, 1u, false> Vector3_r;
typedef Matrix<real_t, 4u, 1u, false> Vector4_r;

typedef MatrixMap<real_t, 3u, 3u> MapMatrix3x3_r;
typedef MatrixMap<real_t, 4u, 4u> MapMatrix4x4_r;

typedef MatrixMap<real_t, 2u, 1u, false> MapVector2_r;
typedef MatrixMap<real_t, 3u, 1u, false> MapVector3_r;
typedef MatrixMap<real_t, 4u, 1u, false> MapVector4_r;

// Implementation:

// Constructors	START
template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline Matrix<S, Rows, Cols, RowMajor>::Matrix()
:	EigenDerived()
{}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline Matrix<S, Rows, Cols, RowMajor>::Matrix(S diagonal)
:	EigenDerived()
{
	for (index_t row = 0; row < Rows; ++row)
		for (index_t col = 0; col < Cols; ++col)
			Eigen::Matrix<S, Rows, Cols, RowMajor ? Eigen::RowMajor : Eigen::ColMajor>
				::operator()(row, col) = (row == col ? S(diagonal) : S(0));
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline Matrix<S, Rows, Cols, RowMajor>::Matrix(const std::array<S, Rows * Cols>& data)
:	EigenDerived()
{
	Eigen::CommaInitializer<EigenDerived> init(*this, data[0]);
	for (index_t i = 1; i < Rows * Cols; ++i)
		init , data[i];
	init.finished();
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline Matrix<S, Rows, Cols, RowMajor>::Matrix(const Matrix<S, Rows, Cols, RowMajor>& mat)
:	EigenDerived(mat)
{}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline Matrix<S, Rows, Cols, RowMajor>::Matrix(
		const EigenDerived& mat)
:	EigenDerived(mat)
{}
// Constructors	END

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline S* Matrix<S, Rows, Cols, RowMajor>::data()
{
	return EigenDerived::data();
}
template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline const S* Matrix<S, Rows, Cols, RowMajor>::data() const
{
	return EigenDerived::data();
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline S& Matrix<S, Rows, Cols, RowMajor>::operator()(index_t row, index_t col)
{
	return EigenDerived::operator()(row, col);
}
template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline const S& Matrix<S, Rows, Cols, RowMajor>::operator()(index_t row, index_t col) const
{
	return EigenDerived::operator()(row, col);
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline Matrix<S, Rows, Cols, RowMajor> Matrix<S, Rows, Cols, RowMajor>::operator*(S scalar) const
{
	return EigenDerived::operator*(scalar);
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline Matrix<S, Rows, Cols, RowMajor> Matrix<S, Rows, Cols, RowMajor>::operator/(S scalar) const
{
	return EigenDerived::operator/(scalar);
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline Matrix<S, Rows, Cols, RowMajor> Matrix<S, Rows, Cols, RowMajor>::operator*=(S scalar)
{
	EigenDerived::operator*=(scalar);
	return *this;
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline Matrix<S, Rows, Cols, RowMajor> Matrix<S, Rows, Cols, RowMajor>::operator/=(S scalar)
{
	EigenDerived::operator/=(scalar);
	return *this;
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
template<unsigned int N, bool RM>
inline Matrix<S, Rows, N, RM> Matrix<S, Rows, Cols, RowMajor>
	::operator*(const Matrix<S, Cols, N, RM>& other) const
{
	return Matrix<S, Rows, N, RM>(EigenDerived::operator*(other));
}
template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
template<unsigned int N, bool RM>
inline Matrix<S, Rows, N, RM> Matrix<S, Rows, Cols, RowMajor>
	::operator*(const MatrixMap<S, Cols, N, RM>& other) const
{
	return Matrix<S, Rows, N, RM>(EigenDerived::operator*(other));
}

// MatrixMap implementation

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline MatrixMap<S, Rows, Cols, RowMajor>::MatrixMap(S* data)
:	EigenDerived(data)
{}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline S* MatrixMap<S, Rows, Cols, RowMajor>::data()
{
	return EigenDerived::data();
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline const S* MatrixMap<S, Rows, Cols, RowMajor>::data() const
{
	return EigenDerived::data();
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline S& MatrixMap<S, Rows, Cols, RowMajor>::operator()(index_t row, index_t col)
{
	return EigenDerived::operator()(row, col);
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline const S& MatrixMap<S, Rows, Cols, RowMajor>::operator()(index_t row, index_t col) const
{
	return EigenDerived::operator()(row, col);
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline Matrix<S, Rows, Cols, RowMajor> math::MatrixMap<S, Rows, Cols, RowMajor>::operator*(S scalar) const
{
	return EigenDerived::operator*(scalar);
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline Matrix<S, Rows, Cols, RowMajor> math::MatrixMap<S, Rows, Cols, RowMajor>::operator/(S scalar) const
{
	return EigenDerived::operator*(scalar);
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline MatrixMap<S, Rows, Cols, RowMajor> MatrixMap<S, Rows, Cols, RowMajor>
	::operator*=(S scalar)
{
	EigenDerived::operator/=(scalar);
	return *this;
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline MatrixMap<S, Rows, Cols, RowMajor> MatrixMap<S, Rows, Cols, RowMajor>
	::operator/=(S scalar)
{
	EigenDerived::operator/=(scalar);
	return *this;
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
template<unsigned int N, bool RM>
inline Matrix<S, Rows, N, RM> MatrixMap<S, Rows, Cols, RowMajor>
	::operator*(const Matrix<S, Cols, N, RM>& other) const
{
	return Matrix<S, Rows, N, RM>(EigenDerived::operator*(other));
}
template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
template<unsigned int N, bool RM>
inline Matrix<S, Rows, N, RM> MatrixMap<S, Rows, Cols, RowMajor>
	::operator*(const MatrixMap<S, Cols, N, RM>& other) const
{
	return Matrix<S, Rows, N, RM>(EigenDerived::operator*(other));
}

}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline std::ostream& operator<<(std::ostream& out, const math::Matrix<S, Rows, Cols, RowMajor>& mat)
{
	out << "Matrix" << Rows << "x" << Cols << " " << (RowMajor ? "Row major" : "Column major") << std::endl;

	for (typename math::Matrix<S, Rows, Cols, RowMajor>::index_t row = 0; row < Rows; ++row)
	{
		out << "|" << " ";
		for (typename math::Matrix<S, Rows, Cols, RowMajor>::index_t col = 0; col < Cols; ++col)
			out << std::fixed
				<< std::showpoint
				<< std::setprecision(3)
				<< std::setw(8)
				<< mat(row, col)
				<< " ";
		out << "|" << std::endl;
	}

	return out;
}

template<typename S, unsigned int Rows, unsigned int Cols, bool RowMajor>
inline std::ostream& operator<<(std::ostream& out, const math::MatrixMap<S, Rows, Cols, RowMajor>& mat)
{
	out << "MatrixMap" << Rows << "x" << Cols << " " << (RowMajor ? "Row major" : "Column major") << std::endl;

	for (typename math::Matrix<S, Rows, Cols, RowMajor>::index_t row = 0; row < Rows; ++row)
	{
		out << "|" << " ";
		for (typename math::Matrix<S, Rows, Cols, RowMajor>::index_t col = 0; col < Cols; ++col)
			out << std::fixed
				<< std::showpoint
				<< std::setprecision(3)
				<< std::setw(8)
				<< mat(row, col)
				<< " ";
		out << "|" << std::endl;
	}

	return out;
}

#endif
