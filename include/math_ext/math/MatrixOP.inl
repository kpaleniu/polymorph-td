
#define MATRIX_TEMPLATES_DECLARATION \
	typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor

#define MATRIX_TEMPLATES \
	Arithmetic, Rows, Cols, RowMajor

#define MATRIX_SQUARE_TEMPLATES_DECLARATION \
	typename Arithmetic, unsigned int Rows, bool RowMajor

#define MATRIX_SQUARE_TEMPLATES \
	Arithmetic, Rows, Rows, RowMajor

#define MATRIX_COLUMN_TEMPLATES_DECLARATION \
	typename Arithmetic, unsigned int Rows, bool RowMajor

#define MATRIX_COLUMN_TEMPLATES \
	Arithmetic, Rows, 1u, RowMajor

#define MATRIX_COLUMN_DYNAMIC_TEMPLATES_DECLARATION \
	typename Arithmetic, bool RowMajor

#define MATRIX_COLUMN_DYNAMIC_TEMPLATES \
	Arithmetic, DYNAMIC, 1u, RowMajor

namespace math {

// Operators:

// Helpers

template <typename Arithmetic, bool RowMajor>
Arithmetic determinant(const MatrixMap<Arithmetic, 3u, 3u, RowMajor>& source)
{
	//
	//      | a b c |
	// det( | d e f | ) = aei + bfg + cdh - ceg - bdi - afh
	//      | g h i |
	//

	const Arithmetic
		a = source(0, 0),
		b = source(0, 1),
		c = source(0, 2),
		d = source(1, 0),
		e = source(1, 1),
		f = source(1, 2),
		g = source(2, 0),
		h = source(2, 1),
		i = source(2, 2);

	return a * e * i
		+ b * f * g
		+ c * d * h
		- c * e * g
		- b * d * i
		- a * f * h;
}

template <typename Arithmetic, bool RowMajor>
Matrix<Arithmetic, 3u, 3u, RowMajor>
	inverse(const MatrixMap<Arithmetic, 3u, 3u, RowMajor>& source)
{
	//
	// | a b c |-1    | A D G |T             | a b c |
	// | d e f |    = | B E H |  * (1 / det( | d e f | ))
	// | g h k |      | C F K |              | g h k |
	//
	// A = (ek - fh)
	// B = -(dk - fg)
	// C = (dh - eg)
	// D = -(bk - ch)
	// E = (ak - cg)
	// F = -(ah - bg)
	// G = (bf - ce)
	// H = -(af - cd)
	// K = (ae - bd)
	//

	const Arithmetic
		a = source(0, 0),
		b = source(0, 1),
		c = source(0, 2),
		d = source(1, 0),
		e = source(1, 1),
		f = source(1, 2),
		g = source(2, 0),
		h = source(2, 1),
		k = source(2, 2);

	const Arithmetic
		A = e * k - f * h,
		B = -(d * k - f * g),
		C = d * h - e * g,
		D = -(b * k - c * h),
		E = a * k - c * g,
		F = -(a * h - b * g),
		G = b * f - c * e,
		H = -(a * f - c * d),
		K = a * e - b * d;

	const Arithmetic invDet = Arithmetic(1) / determinant(source);

	Matrix<Arithmetic, 3u, 3u, RowMajor> target;

	target(0, 0) = A;
	target(1, 0) = B;
	target(2, 0) = C;
	target(0, 1) = D;
	target(1, 1) = E;
	target(2, 1) = F;
	target(0, 2) = G;
	target(1, 2) = H;
	target(2, 2) = K;

	target *= invDet;

	return target;
}

template <typename Arithmetic, bool RowMajor>
Matrix<Arithmetic, 3u, 1u, RowMajor>
	crossProduct(const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& v1,
	const MatrixMap<Arithmetic, 3u, 1u, RowMajor>& v2)
{
	Matrix<Arithmetic, 3u, 1u, RowMajor> rVec;

	rVec[0] = v1[1] * v2[2] - v1[2] * v2[1];
	rVec[1] = v1[2] * v2[0] - v1[0] * v2[2];
	rVec[2] = v1[0] * v2[1] - v1[1] * v2[0];

	return rVec;
}

//  Matrix-Matrix operators:

template <MATRIX_TEMPLATES_DECLARATION>
Matrix<MATRIX_TEMPLATES> operator+(const MatrixMap<MATRIX_TEMPLATES>& m1,
									const MatrixMap<MATRIX_TEMPLATES>& m2)
{
	Matrix<MATRIX_TEMPLATES> rMat;

	for (index_t k = 0; k < Rows * Cols; ++k)
		rMat.data()[k] = m1.data()[k] + m2.data()[k];

	return rMat;
}

template <MATRIX_TEMPLATES_DECLARATION>
MatrixMap<MATRIX_TEMPLATES>& operator+=(MatrixMap<MATRIX_TEMPLATES>& m1,
										const MatrixMap<MATRIX_TEMPLATES>& m2)
{
	for (index_t k = 0; k < Rows * Cols; ++k)
		m1.data()[k] += m2.data()[k];

	return m1;
}

template <MATRIX_TEMPLATES_DECLARATION>
Matrix<MATRIX_TEMPLATES> operator-(const MatrixMap<MATRIX_TEMPLATES>& m1,
									const MatrixMap<MATRIX_TEMPLATES>& m2)
{
	Matrix<MATRIX_TEMPLATES> rMat;

	for (index_t k = 0; k < Rows * Cols; ++k)
		rMat.data()[k] = m1.data()[k] - m2.data()[k];

	return rMat;
}

template <MATRIX_TEMPLATES_DECLARATION>
MatrixMap<MATRIX_TEMPLATES>& operator-=(MatrixMap<MATRIX_TEMPLATES>& m1,
										const MatrixMap<MATRIX_TEMPLATES>& m2)
{
	for (index_t k = 0; k < Rows * Cols; ++k)
		m1.data()[k] -= m2.data()[k];

	return m1;
}

template<typename Arithmetic,
		 unsigned int Rows1,
		 unsigned int Cols1_Rows2,
		 unsigned int Cols2,
		 bool RowMajor>
Matrix<Arithmetic, Rows1, Cols2, RowMajor>
	operator*(const MatrixMap<Arithmetic, Rows1, Cols1_Rows2, RowMajor>& m1,
			  const MatrixMap<Arithmetic, Cols1_Rows2, Cols2, RowMajor>& m2)
{
	Matrix<Arithmetic, Rows1, Cols2, RowMajor> rMat;

	for (index_t row = 0; row < m1.rows(); ++row)
	{
		for (index_t col = 0; col < m2.cols(); ++col)
		{
			Arithmetic& value = rMat(row, col);

			value = Arithmetic(0);

			for (index_t k = 0; k < m2.rows(); ++k)
				value += m1(row, k) * m2(k, col);
		}
	}

	return rMat;
}

// Self multiplication, square matrices only.
template <MATRIX_SQUARE_TEMPLATES_DECLARATION>
MatrixMap<MATRIX_SQUARE_TEMPLATES>&	operator*=(MatrixMap<MATRIX_SQUARE_TEMPLATES>& m1,
												const MatrixMap<MATRIX_SQUARE_TEMPLATES>& m2)
{
	Matrix<MATRIX_SQUARE_TEMPLATES> temp = m1 * m2;
	return m1 = temp;
}

// Dot-product, vectors only.
template <MATRIX_COLUMN_TEMPLATES_DECLARATION>
Arithmetic operator*(const MatrixMap<MATRIX_COLUMN_TEMPLATES>& v1,
						const MatrixMap<MATRIX_COLUMN_TEMPLATES>& v2)
{
	Arithmetic rVal(0);

	for (index_t k = 0; k < Rows; ++k)
		rVal += v1.data()[k] * v2.data()[k];

	return rVal;
}

//  Scalar-Matrix operators:

template <MATRIX_TEMPLATES_DECLARATION>
Matrix<MATRIX_TEMPLATES> operator*(const MatrixMap<MATRIX_TEMPLATES>& m,
									Arithmetic s)
{
	Matrix<MATRIX_TEMPLATES> rMat;

	for (index_t k = 0; k < Rows * Cols; ++k)
		rMat.data()[k] = m.data()[k] * s;

	return rMat;
}

template <MATRIX_TEMPLATES_DECLARATION>
MatrixMap<MATRIX_TEMPLATES>& operator*=(MatrixMap<MATRIX_TEMPLATES>& m,
										Arithmetic s)
{
	for (index_t k = 0; k < Rows * Cols; ++k)
		m.data()[k] *= s;

	return m;
}

template <MATRIX_TEMPLATES_DECLARATION>
Matrix<MATRIX_TEMPLATES> operator*(Arithmetic s, const MatrixMap<MATRIX_TEMPLATES>& m)
{
	Matrix<MATRIX_TEMPLATES> rMat;

	for (index_t k = 0; k < Rows * Cols; ++k)
		rMat.data()[k] = m.data()[k] * s;

	return rMat;
}

template <MATRIX_TEMPLATES_DECLARATION>
Matrix<MATRIX_TEMPLATES> operator/(const MatrixMap<MATRIX_TEMPLATES>& m, Arithmetic s)
{
	Matrix<MATRIX_TEMPLATES> rMat;

	for (index_t k = 0; k < Rows * Cols; ++k)
		rMat.data()[k] = m.data()[k] / s;

	return rMat;
}

template <MATRIX_TEMPLATES_DECLARATION>
MatrixMap<MATRIX_TEMPLATES>& operator/=(const MatrixMap<MATRIX_TEMPLATES>& m, Arithmetic s)
{
	for (index_t k = 0; k < Rows * Cols; ++k)
		m.data()[k] /= s;

	return m;
}

//  Unary operators:

template <MATRIX_TEMPLATES_DECLARATION>
Matrix<MATRIX_TEMPLATES> operator-(const MatrixMap<MATRIX_TEMPLATES>& m)
{
	Matrix<MATRIX_TEMPLATES> rMat;

	for (index_t k = 0; k < Rows * Cols; ++k)
		rMat.data()[k] = -m.data()[k];

	return rMat;
}

//  Comparison operators:

template <MATRIX_TEMPLATES_DECLARATION>
bool operator==(const MatrixMap<MATRIX_TEMPLATES>& m1,
				const MatrixMap<MATRIX_TEMPLATES>& m2)
{
	if (&m1 == &m2)
		return true;

	for (index_t k = 0; k < Rows * Cols; ++k)
		if (m1.data()[k] != m2.data()[k])
			return false;

	return true;
}

template <MATRIX_TEMPLATES_DECLARATION>
bool operator!=(const MatrixMap<MATRIX_TEMPLATES>& m1,
				const MatrixMap<MATRIX_TEMPLATES>& m2)
{
	return !(m1 == m2);
}


}


#undef MATRIX_TEMPLATES_DECLARATION
#undef MATRIX_TEMPLATES
#undef MATRIX_SQUARE_TEMPLATES_DECLARATION
#undef MATRIX_SQUARE_TEMPLATES
#undef MATRIX_COLUMN_TEMPLATES_DECLARATION
#undef MATRIX_COLUMN_TEMPLATES
#undef MATRIX_COLUMN_DYNAMIC_TEMPLATES_DECLARATION
#undef MATRIX_COLUMN_DYNAMIC_TEMPLATES