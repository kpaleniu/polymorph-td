#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "math/types.hpp"

#include <Cpp11.hpp>

#include <ostream>
#include <iomanip>
#include <array>
#include <initializer_list>

namespace math {

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
class MatrixMap;

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
class Matrix;

template <typename Arithmetic, bool RowMajor>
Arithmetic determinant(const MatrixMap<Arithmetic, 3u, 3u, RowMajor>& source);

template <typename Arithmetic, bool RowMajor>
Matrix<Arithmetic, 3u, 3u, RowMajor> inverse(const MatrixMap<Arithmetic, 3u, 3u, RowMajor>& source);


// Generic matrix.

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor=false>
class Matrix : public MatrixMap<Arithmetic, Rows, Cols, RowMajor>
{
public:
	typedef unsigned int index_t;

	Matrix();

	Matrix(const Arithmetic* data);
	Matrix(const Matrix<Arithmetic, Rows, Cols, RowMajor>& mat);

	static const Matrix<Arithmetic, Rows, Cols, RowMajor> ZERO;

private:
	Arithmetic _data[Rows * Cols];
};


// Square matrix.

template <typename Arithmetic, unsigned int Rows, bool RowMajor>
class Matrix<Arithmetic, Rows, Rows, RowMajor> : public MatrixMap<Arithmetic, Rows, Rows, RowMajor>
{
public:
	typedef unsigned int index_t;

	Matrix();
	Matrix(Arithmetic diagonal);

	Matrix(const Arithmetic* data);
	Matrix(const Matrix<Arithmetic, Rows, Rows, RowMajor>& mat);

	static const Matrix<Arithmetic, Rows, Rows, RowMajor> ZERO;
	static const Matrix<Arithmetic, Rows, Rows, RowMajor> IDENTITY;

private:
	Arithmetic _data[Rows * Rows];
};


// Column matrix (vector).

template <typename Arithmetic, unsigned int Rows, bool RowMajor>
class Matrix<Arithmetic, Rows, 1u, RowMajor> : public MatrixMap<Arithmetic, Rows, 1u, RowMajor>
{
public:
	typedef unsigned int index_t;

	Matrix();
	Matrix(std::initializer_list<Arithmetic> data);

	Matrix(const Arithmetic* data);
	Matrix(const Matrix<Arithmetic, Rows, 1u, RowMajor>& mat);

	static const Matrix<Arithmetic, Rows, 1u, RowMajor> ZERO;

private:
	Arithmetic _data[Rows];
};



// Generic matrix map.

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor=false>
class MatrixMap
{
public:
	typedef unsigned int index_t;

	// typedef detail::Constants<Arithmetic, Rows, Cols, RowMajor> Constants;

	MatrixMap();
	MatrixMap(Arithmetic* data);
	MatrixMap(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other);

	Arithmetic* data();
	const Arithmetic* data() const;

	Arithmetic& operator()(index_t row, index_t col);
	const Arithmetic& operator()(index_t row, index_t col) const;

	Matrix<Arithmetic, Rows, Cols, RowMajor> operator*(Arithmetic scalar) const;
	Matrix<Arithmetic, Rows, Cols, RowMajor> operator/(Arithmetic scalar) const;
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>& operator*=(Arithmetic scalar);
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>& operator/=(Arithmetic scalar);

	Matrix<Arithmetic, Cols, Rows, RowMajor> transpose() const;

	template<unsigned int N>
	Matrix<Arithmetic, Rows, N, RowMajor> operator*(const MatrixMap<Arithmetic, Cols, N, RowMajor>& other) const;

	bool operator==(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other) const;
	bool operator!=(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other) const;

#ifdef NO_TEMPLATE_FRIENDS
	public:
#else
	private:
#endif

	Arithmetic* _mappedData;

#ifndef NO_TEMPLATE_FRIENDS
	template <unsigned int Rows2, unsigned int Cols2>
	friend class MatrixMap<Arithmetic, Rows2, Cols2, RowMajor>;
#endif
};

// Square matrix map.

template <typename Arithmetic, unsigned int Rows, bool RowMajor>
class MatrixMap<Arithmetic, Rows, Rows, RowMajor>
{
public:
	typedef unsigned int index_t;

	// typedef detail::Constants<Arithmetic, Rows, Cols, RowMajor> Constants;

	MatrixMap();
	MatrixMap(Arithmetic* data);
	MatrixMap(const MatrixMap<Arithmetic, Rows, Rows, RowMajor>& other);

	Arithmetic* data();
	const Arithmetic* data() const;

	Arithmetic length() const;
	Arithmetic lengthSquared() const;

	Arithmetic& operator()(index_t row, index_t col = 0);
	const Arithmetic& operator()(index_t row, index_t col = 0) const;

	Matrix<Arithmetic, Rows, Rows, RowMajor> operator*(Arithmetic scalar) const;
	Matrix<Arithmetic, Rows, Rows, RowMajor> operator/(Arithmetic scalar) const;
	MatrixMap<Arithmetic, Rows, Rows, RowMajor>& operator*=(Arithmetic scalar);
	MatrixMap<Arithmetic, Rows, Rows, RowMajor>& operator/=(Arithmetic scalar);

	Matrix<Arithmetic, Rows, Rows, RowMajor> transpose() const;
	MatrixMap<Arithmetic, Rows, Rows, RowMajor>& transposeSelf();

	template<unsigned int N>
	Matrix<Arithmetic, Rows, N, RowMajor> operator*(const MatrixMap<Arithmetic, Rows, N, RowMajor>& other) const;

	MatrixMap<Arithmetic, Rows, Rows, RowMajor>& operator*=(const MatrixMap<Arithmetic, Rows, Rows, RowMajor>& other) const;

	bool operator==(const MatrixMap<Arithmetic, Rows, Rows, RowMajor>& other) const;
	bool operator!=(const MatrixMap<Arithmetic, Rows, Rows, RowMajor>& other) const;

#ifdef NO_TEMPLATE_FRIENDS
	public:
#else
	private:
#endif

	Arithmetic* _mappedData;

#ifndef NO_TEMPLATE_FRIENDS
	template <unsigned int Rows2, unsigned int Cols2>
	friend class MatrixMap<Arithmetic, Rows2, Cols2, RowMajor>;
#endif
};


// Row matrix map.

template <typename Arithmetic, unsigned int Rows, bool RowMajor>
class MatrixMap<Arithmetic, Rows, 1u, RowMajor>
{
public:
	typedef unsigned int index_t;

	// typedef detail::Constants<Arithmetic, Rows, Cols, RowMajor> Constants;

	MatrixMap();
	MatrixMap(Arithmetic* data);
	MatrixMap(const MatrixMap<Arithmetic, Rows, 1u, RowMajor>& other);

	Arithmetic* data();
	const Arithmetic* data() const;

	Arithmetic& operator()(index_t row, index_t col = 0);
	const Arithmetic& operator()(index_t row, index_t col = 0) const;

	Arithmetic& operator[](index_t row);
	const Arithmetic& operator[](index_t row) const;

	Matrix<Arithmetic, Rows, 1u, RowMajor> operator*(Arithmetic scalar) const;
	Matrix<Arithmetic, Rows, 1u, RowMajor> operator/(Arithmetic scalar) const;
	MatrixMap<Arithmetic, Rows, 1u, RowMajor>& operator*=(Arithmetic scalar);
	MatrixMap<Arithmetic, Rows, 1u, RowMajor>& operator/=(Arithmetic scalar);

	template<unsigned int N>
	Matrix<Arithmetic, Rows, N, RowMajor> operator*(const MatrixMap<Arithmetic, 1u, N, RowMajor>& other) const;

	Matrix<Arithmetic, 1u, Rows, RowMajor> transpose() const;

	Arithmetic length() const;
	Arithmetic lengthSquared() const;

	bool operator==(const MatrixMap<Arithmetic, Rows, 1u, RowMajor>& other) const;
	bool operator!=(const MatrixMap<Arithmetic, Rows, 1u, RowMajor>& other) const;

#ifdef NO_TEMPLATE_FRIENDS
	public:
#else
	private:
#endif

	Arithmetic* _mappedData;

#ifndef NO_TEMPLATE_FRIENDS
	template <unsigned int Rows2, unsigned int Cols2>
	friend class MatrixMap<Arithmetic, Rows2, Cols2, RowMajor>;
#endif
};

}

#include "math/Matrix.inl"

#endif
