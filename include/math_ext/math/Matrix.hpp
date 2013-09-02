#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "math/types.hpp"

#include <Cpp11.hpp>

#include <ostream>
#include <iomanip>
#include <array>
#include <initializer_list>

#include "math/MatrixOP.hpp"
#include "math/MatrixMap.hpp"
#include "math/MatrixMap.inl"

namespace math {

// Generic
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor = false>
class Matrix : public MatrixMap<Arithmetic, Rows, Cols, RowMajor>
{
public:
	Matrix();
	Matrix(const Matrix<Arithmetic, Rows, Cols, RowMajor>& mat);
	Matrix<Arithmetic, Rows, Cols, RowMajor>&
		operator=(const Matrix<Arithmetic, Rows, Cols, RowMajor>& other);


	Matrix(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& mat);
	Matrix(const Arithmetic* data);

	Matrix<Arithmetic, Rows, Cols, RowMajor>&
		operator=(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other);

	static const Matrix<Arithmetic, Rows, Cols, RowMajor> ZERO;

private:
	Arithmetic _data[Rows * Cols];
};

// Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
class Matrix<Arithmetic, Rows, Rows, RowMajor> :
	public MatrixMap<Arithmetic, Rows, Rows, RowMajor>
{
public:
	Matrix();
	Matrix(const Matrix<Arithmetic, Rows, Rows, RowMajor>& mat);
	Matrix<Arithmetic, Rows, Rows, RowMajor>&
		operator=(const Matrix<Arithmetic, Rows, Rows, RowMajor>& other);


	Matrix(const MatrixMap<Arithmetic, Rows, Rows, RowMajor>& mat);
	Matrix(const Arithmetic* data);
	explicit Matrix(Arithmetic data);

	Matrix<Arithmetic, Rows, Rows, RowMajor>&
		operator=(const MatrixMap<Arithmetic, Rows, Rows, RowMajor>& other);

	static const Matrix<Arithmetic, Rows, Rows, RowMajor> ZERO;
	static const Matrix<Arithmetic, Rows, Rows, RowMajor> IDENTITY;

private:
	Arithmetic _data[Rows * Rows];
};

// Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
class Matrix<Arithmetic, Rows, 1u, RowMajor> :
	public MatrixMap<Arithmetic, Rows, 1u, RowMajor>
{
public:
	Matrix();
	Matrix(const Matrix<Arithmetic, Rows, 1u, RowMajor>& mat);
	Matrix<Arithmetic, Rows, 1u, RowMajor>&
		operator=(const Matrix<Arithmetic, Rows, 1u, RowMajor>& other);


	Matrix(const MatrixMap<Arithmetic, Rows, 1u, RowMajor>& mat);
	Matrix(const std::initializer_list<Arithmetic>& data);
	Matrix(const Arithmetic* data);

	Matrix<Arithmetic, Rows, 1u, RowMajor>&
		operator=(const MatrixMap<Arithmetic, Rows, 1u, RowMajor>& other);

	static const Matrix<Arithmetic, Rows, 1u, RowMajor> ZERO;

private:
	Arithmetic _data[Rows];
};

template <typename Arithmetic, unsigned int Rows, bool RowMajor>
class Matrix<Arithmetic, Rows, DYNAMIC, RowMajor>
{
	//static_assert(false, "DYNAMIC matrices not allowed.");
};

template <typename Arithmetic, unsigned int Cols, bool RowMajor>
class Matrix<Arithmetic, DYNAMIC, Cols, RowMajor>
{
	//static_assert(false, "DYNAMIC matrices not allowed.");
};

template <typename Arithmetic, bool RowMajor>
class Matrix<Arithmetic, DYNAMIC, DYNAMIC, RowMajor>
{
	//static_assert(false, "DYNAMIC matrices not allowed.");
};

}

#include "math/Matrix.inl"

#include "math/MatrixOP.inl"

#endif
