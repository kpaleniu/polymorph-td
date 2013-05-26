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


template<typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor=false>
class Matrix : public MatrixMap<Arithmetic, Rows, Cols, RowMajor>
{
public:
	typedef unsigned int index_t;

	/** Creates a zero matrix. */
	Matrix();
	/** Creates a matrix with specified value in diagonal, others are zero. */
	Matrix(Arithmetic diagonal);

	Matrix(const Arithmetic* data);
	Matrix(const Matrix<Arithmetic, Rows, Cols, RowMajor>& mat);

private:
	Arithmetic _data[Rows * Cols];
};

namespace detail {

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor=false, bool Square = (Rows == Cols)>
struct Constants
{
	static const Matrix<Arithmetic, Rows, Cols, RowMajor> ZERO;
	static const Matrix<Arithmetic, Rows, Cols, RowMajor> IDENTITY;
};

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
struct Constants<Arithmetic, Rows, Cols, RowMajor, false>
{
	static const Matrix<Arithmetic, Rows, Cols, RowMajor> ZERO;
};

}



template <typename Arithmetic, bool RowMajor>
Arithmetic determinant(const MatrixMap<Arithmetic, 3u, 3u, RowMajor>& source);

template <typename Arithmetic, bool RowMajor>
Matrix<Arithmetic, 3u, 3u, RowMajor> inverse(const MatrixMap<Arithmetic, 3u, 3u, RowMajor>& source);



template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor=false>
class MatrixMap
{
public:
	typedef unsigned int index_t;

	typedef detail::Constants<Arithmetic, Rows, Cols, RowMajor> Constants;

	MatrixMap();
	MatrixMap(Arithmetic* data);
	MatrixMap(const MatrixMap& other);

	Arithmetic* data();
	const Arithmetic* data() const;

	Arithmetic& operator()(index_t row, index_t col);
	const Arithmetic& operator()(index_t row, index_t col) const;

	Matrix<Arithmetic, Rows, Cols, RowMajor> operator*(Arithmetic scalar) const;
	Matrix<Arithmetic, Rows, Cols, RowMajor> operator/(Arithmetic scalar) const;
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>& operator*=(Arithmetic scalar);
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>& operator/=(Arithmetic scalar);

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

}

#include "math/Matrix.inl"

#endif
