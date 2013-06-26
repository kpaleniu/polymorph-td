#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "math/types.hpp"

#include <Cpp11.hpp>

#include <ostream>
#include <iomanip>
#include <array>
#include <initializer_list>

namespace math {

enum Dimension
{
	DYNAMIC = 0
};

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


	using MatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator=;

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

	using MatrixMap<Arithmetic, Rows, Rows, RowMajor>::operator=;

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


	using MatrixMap<Arithmetic, Rows, 1u, RowMajor>::operator=;

private:
	Arithmetic _data[Rows];
};

namespace detail {

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
class CommonMatrixMap
{
public:
	typedef unsigned int index_t;

	CommonMatrixMap(Arithmetic* data);

	Arithmetic* data();
	const Arithmetic* data() const;

	Arithmetic& operator()(index_t row, index_t col);
	const Arithmetic& operator()(index_t row, index_t col) const;

	Matrix<Arithmetic, Rows, Cols, RowMajor> operator*(Arithmetic scalar) const;
	Matrix<Arithmetic, Rows, Cols, RowMajor> operator/(Arithmetic scalar) const;
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>& operator*=(Arithmetic scalar);
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>& operator/=(Arithmetic scalar);
	

	Matrix<Arithmetic, Rows, Cols, RowMajor> 
		operator+(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other) const;
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>&
		operator+=(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other);
	Matrix<Arithmetic, Rows, Cols, RowMajor> 
		operator-(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other) const;
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>&
		operator-=(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other);

	CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>& 
		operator=(const CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>& other);

	Matrix<Arithmetic, Cols, Rows, RowMajor> transpose() const;

	template<unsigned int N>
	Matrix<Arithmetic, Rows, N, RowMajor> operator*(const MatrixMap<Arithmetic, Cols, N, RowMajor>& other) const;

	bool operator==(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other) const;
	bool operator!=(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other) const;


#ifndef NO_TEMPLATE_FRIENDS
	protected:
#else
	public:
#endif

	Arithmetic* _mappedData;

#ifndef NO_TEMPLATE_FRIENDS
	template <typename Arithmetic2, unsigned int Rows2, unsigned int Cols2>
	friend class CommonMatrixMap<Arithmetic2, Rows2, Cols2, RowMajor>;
#endif

private:
	CommonMatrixMap(const CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>&) {}
};

template <typename Arithmetic, bool RowMajor>
class CommonMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>
{
public:
	typedef unsigned int index_t;
	typedef unsigned int size_t;

	CommonMatrixMap(Arithmetic* data, size_t rows);

	Arithmetic* data();
	const Arithmetic* data() const;

	Arithmetic& operator()(index_t row, index_t col);
	const Arithmetic& operator()(index_t row, index_t col) const;
	
	MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>& operator*=(Arithmetic scalar);
	MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>& operator/=(Arithmetic scalar);
	
	MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>&
		operator+=(const MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>& other);
	MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>&
		operator-=(const MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>& other);

	CommonMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>& 
		operator=(const CommonMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>& other);

	bool operator==(const MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>& other) const;
	bool operator!=(const MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>& other) const;

#ifndef NO_TEMPLATE_FRIENDS
	protected:
#else
	public:
#endif

	Arithmetic* _mappedData;
	size_t _rows;

#ifndef NO_TEMPLATE_FRIENDS
	template <typename Arithmetic2, unsigned int Rows2, unsigned int Cols2>
	friend class CommonMatrixMap<Arithmetic2, Rows2, Cols2, RowMajor>;
#endif

private:
	CommonMatrixMap(const CommonMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>&) {}
};

}

// Generic matrix map.

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor=false>
class MatrixMap : 
	public detail::CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>
{
public:
	MatrixMap();
	MatrixMap(Arithmetic* data);

	MatrixMap<Arithmetic, Rows, Cols, RowMajor>& 
		operator=(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other);

private:
	MatrixMap(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>&) {}
};

// Square matrix map.

template <typename Arithmetic, unsigned int Rows, bool RowMajor>
class MatrixMap<Arithmetic, Rows, Rows, RowMajor> : 
	public detail::CommonMatrixMap<Arithmetic, Rows, Rows, RowMajor>
{
public:
	MatrixMap();
	MatrixMap(Arithmetic* data);

	MatrixMap<Arithmetic, Rows, Rows, RowMajor>& transposeSelf();

	using detail::CommonMatrixMap<Arithmetic, Rows, Rows, RowMajor>::operator*=;
	MatrixMap<Arithmetic, Rows, Rows, RowMajor>& 
		operator*=(const MatrixMap<Arithmetic, Rows, Rows, RowMajor>& other);

	MatrixMap<Arithmetic, Rows, Rows, RowMajor>& 
		operator=(const MatrixMap<Arithmetic, Rows, Rows, RowMajor>& other);

private:
	MatrixMap(const MatrixMap<Arithmetic, Rows, Rows, RowMajor>&) {}
};


// Column matrix map.

template <typename Arithmetic, unsigned int Rows, bool RowMajor>
class MatrixMap<Arithmetic, Rows, 1u, RowMajor> :
	public detail::CommonMatrixMap<Arithmetic, Rows, 1u, RowMajor>
{
public:
	typedef unsigned int index_t;

	// typedef detail::Constants<Arithmetic, Rows, Cols, RowMajor> Constants;

	MatrixMap();
	MatrixMap(Arithmetic* data);

	Arithmetic& operator[](index_t row);
	const Arithmetic& operator[](index_t row) const;

	Arithmetic length() const;
	Arithmetic lengthSquared() const;

	MatrixMap<Arithmetic, Rows, 1u, RowMajor>& 
		operator=(const MatrixMap<Arithmetic, Rows, 1u, RowMajor>& other);

private:
	MatrixMap(const MatrixMap<Arithmetic, Rows, 1u, RowMajor>&) {}
};

// Dynamic column matrix map.

template <typename Arithmetic, bool RowMajor>
class MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor> :
	public detail::CommonMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>
{
public:
	typedef unsigned int index_t;

	MatrixMap();
	MatrixMap(Arithmetic* data, size_t size);

	Arithmetic& operator[](index_t row);
	const Arithmetic& operator[](index_t row) const;

	Arithmetic length() const;
	Arithmetic lengthSquared() const;

	size_t rows() const;

	MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>& 
		operator=(const MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>& other);

private:
	MatrixMap(const MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>&) {}
};

}

#include "math/Matrix.inl"

#endif
