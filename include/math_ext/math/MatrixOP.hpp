#ifndef MATRIX_OP_HPP_
#define MATRIX_OP_HPP_

namespace math {

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
class MatrixMap;
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
class Matrix;


template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
MatrixMap<Arithmetic, Rows, Cols, RowMajor> &
	operator*=(MatrixMap<Arithmetic, Rows, Cols, RowMajor>& m, Arithmetic s);

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
MatrixMap<Arithmetic, Rows, Cols, RowMajor> &
	operator/=(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& m, Arithmetic s);

//  Unary operators:

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>
	operator-(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& m);

//  Comparison operators:

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
bool operator==(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& m1,
				const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& m2);

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
bool operator!=(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& m1,
				const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& m2);


template <typename Arithmetic, bool RowMajor>
Arithmetic determinant(const MatrixMap<Arithmetic, 3u, 3u, RowMajor>& source);

template <typename Arithmetic, bool RowMajor>
Matrix<Arithmetic, 3u, 3u, RowMajor> inverse(const MatrixMap<Arithmetic, 3u, 3u, RowMajor>& source);

template <typename Arithmetic, bool RowMajor>
Matrix<Arithmetic, 3u, 1u, RowMajor>
	crossProduct(const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& v1,
				 const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& v2);

// Operators:

//  Matrix-Matrix operators:

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>
	operator+(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& m1,
			  const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& m2);

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
MatrixMap<Arithmetic, Rows, Cols, RowMajor> &
	operator+=(MatrixMap<Arithmetic, Rows, Cols, RowMajor>& m1,
			   const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& m2);

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>
	operator-(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& m1,
			  const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& m2);

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
MatrixMap<Arithmetic, Rows, Cols, RowMajor> &
	operator-=(MatrixMap<Arithmetic, Rows, Cols, RowMajor>& m1,
			   const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& m2);

template <typename Arithmetic, 
		  unsigned int Rows1, 
		  unsigned int Cols1_Rows2, 
		  unsigned int Cols2,
		  bool RowMajor>
Matrix<Arithmetic, Rows1, Cols2, RowMajor>
	operator*(const MatrixMap<Arithmetic, Rows1, Cols1_Rows2, RowMajor>& m1,
			  const MatrixMap<Arithmetic, Cols1_Rows2, Cols2, RowMajor>& m2);

// Self multiplication, square matrices only.
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
MatrixMap<Arithmetic, Rows, Rows, RowMajor> &
	operator*=(MatrixMap<Arithmetic, Rows, Rows, RowMajor>& m1,
			   const MatrixMap<Arithmetic, Rows, Rows, RowMajor>& m2);

// Dot-product, vectors only.
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Arithmetic
	operator*(const MatrixMap<Arithmetic, Rows, 1u, RowMajor>& v1,
			  const MatrixMap<Arithmetic, Rows, 1u, RowMajor>& v2);

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>
	operator*(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& m, Arithmetic s);

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>
	operator*(Arithmetic s, const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& m);

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>
	operator/(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& m, Arithmetic s);

}

#endif