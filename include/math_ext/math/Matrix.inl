#include "math/Matrix.hpp"

#include <memory>
#include <type_traits>

namespace math {

namespace detail {

template <typename Index, unsigned int Rows, unsigned int Cols, bool RowMajor>
Index storageIndex(Index row, Index col)
{
	return (RowMajor ? (row * Cols + col) : (col * Rows + row));
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor, bool Square>
const Matrix<Arithmetic, Rows, Cols, RowMajor> 
	Constants<Arithmetic, Rows, Cols, RowMajor, Square>::ZERO = Matrix<Arithmetic, Rows, Cols, RowMajor>();

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
const Matrix<Arithmetic, Rows, Cols, RowMajor>
	Constants<Arithmetic, Rows, Cols, RowMajor, false>::ZERO = Matrix<Arithmetic, Rows, Cols, RowMajor>();

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor, bool Square>
const Matrix<Arithmetic, Rows, Cols, RowMajor> 
	Constants<Arithmetic, Rows, Cols, RowMajor, Square>::IDENTITY(Arithmetic(1));

}

// Matrix

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>::Matrix()
:	MatrixMap<Arithmetic, Rows, Cols, RowMajor>()
{
	for (index_t i = 0; i < Rows * Cols; ++i)
		_data[i] = Arithmetic(0);

	_mappedData = _data;
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>::Matrix(Arithmetic value)
:	MatrixMap<Arithmetic, Rows, Cols, RowMajor>()
{
	for (index_t row = 0; row < Rows; ++row)
	{
		for (index_t col = 0; col < Cols; ++col)
		{
			auto index = detail::storageIndex<index_t, Rows, Cols, RowMajor>(row, col);
			if (col == row)
				_data[index] = value;
			else
				_data[index] = Arithmetic(0);
		}
	}

	_mappedData = _data;
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>::Matrix(const Arithmetic* data)
:	MatrixMap<Arithmetic, Rows, Cols, RowMajor>()
{
	memcpy(_data, data, sizeof(Arithmetic) * Rows * Cols);
	
	_mappedData = _data;
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>::Matrix(const Matrix<Arithmetic, Rows, Cols, RowMajor>& other)
:	MatrixMap<Arithmetic, Rows, Cols, RowMajor>()
{
	memcpy(_data, other._data, sizeof(Arithmetic) * Rows * Cols);

	_mappedData = _data;
}


// MatrixMap

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

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
MatrixMap<Arithmetic, Rows, Cols, RowMajor>::MatrixMap(Arithmetic* data)
:	_mappedData(data)
{
	static_assert
	(
		std::is_arithmetic<Arithmetic>::value, 
		"Template 'Arithmetic' isn't arithmetic."
	);

	static_assert
	(
		(Rows > 0) && (Cols > 0),
		"Bad dimension of matrix."
	);
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
MatrixMap<Arithmetic, Rows, Cols, RowMajor>::MatrixMap(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other)
:	_mappedData(other._mappedData)
{}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
MatrixMap<Arithmetic, Rows, Cols, RowMajor>::MatrixMap()
:	_mappedData(nullptr)
{}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Arithmetic* 
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>::data()
{
	return _mappedData;
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
const Arithmetic* 
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>::data() const
{
	return _mappedData;
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Arithmetic& 
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator()(index_t row, index_t col)
{
	return _mappedData[ detail::storageIndex<index_t, Rows, Cols, RowMajor>(row, col) ];
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
const Arithmetic& 
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator()(index_t row, index_t col) const
{
	return _mappedData[ detail::storageIndex<index_t, Rows, Cols, RowMajor>(row, col) ];
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator*(Arithmetic scalar) const
{
	Arithmetic buffer[Rows * Cols];

	for (index_t i = 0; i < Rows * Cols; ++i)
		buffer[i] = _mappedData[i] * scalar;

	return Matrix<Arithmetic, Rows, Cols, RowMajor>(buffer);
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator/(Arithmetic scalar) const
{
	Arithmetic buffer[Rows * Cols];

	for (index_t i = 0; i < Rows * Cols; ++i)
		buffer[i] = _mappedData[i] / scalar;

	return Matrix<Arithmetic, Rows, Cols, RowMajor>(buffer);
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
MatrixMap<Arithmetic, Rows, Cols, RowMajor>&
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator*=(Arithmetic scalar)
{
	for (index_t i = 0; i < Rows * Cols; ++i)
		_mappedData[i] *= scalar;

	return *this;
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
MatrixMap<Arithmetic, Rows, Cols, RowMajor>&
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator/=(Arithmetic scalar)
{
	for (index_t i = 0; i < Rows * Cols; ++i)
		_mappedData[i] /= scalar;

	return *this;
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
template <unsigned int N>
Matrix<Arithmetic, Rows, N, RowMajor>
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator*(const MatrixMap<Arithmetic, Cols, N, RowMajor>& other) const
{
	Arithmetic buffer[Rows * N];

	for (index_t row = 0; row < Rows; ++row)
	{
		for (index_t col = 0; col < N; ++col)
		{
			Arithmetic& value(buffer[ detail::storageIndex<index_t, Rows, N, RowMajor>(row, col) ]);
			
			value = Arithmetic(0);
			for (index_t k = 0; k < Rows; ++k)
			{
				value += 
				(
					_mappedData[ detail::storageIndex<index_t, Rows, Cols, RowMajor>(row, k) ]
					* other._mappedData[ detail::storageIndex<index_t, Cols, N, RowMajor>(k, col) ] 
				);
			}
		}
	}

	return Matrix<Arithmetic, Rows, N, RowMajor>(buffer);
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
bool MatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator==(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other) const
{
	for (index_t i = 0; i < Rows * Cols; ++i)
		if (_mappedData[i] != other._mappedData[i])
			return false;
	
	return true;
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
bool MatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator!=(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other) const
{
	return !(*this == other);
}

}