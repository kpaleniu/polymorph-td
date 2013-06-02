#include "math/Matrix.hpp"

#include <Assert.hpp>
#include <memory>
#include <type_traits>

namespace math {

namespace detail {

template <typename Index, unsigned int Rows, unsigned int Cols, bool RowMajor>
Index storageIndex(Index row, Index col)
{
	return (RowMajor ? (row * Cols + col) : (col * Rows + row));
}

/*
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor, bool Square>
const Matrix<Arithmetic, Rows, Cols, RowMajor> 
	Constants<Arithmetic, Rows, Cols, RowMajor, Square>::ZERO = Matrix<Arithmetic, Rows, Cols, RowMajor>();

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
const Matrix<Arithmetic, Rows, Cols, RowMajor>
	Constants<Arithmetic, Rows, Cols, RowMajor, false>::ZERO = Matrix<Arithmetic, Rows, Cols, RowMajor>();

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor, bool Square>
const Matrix<Arithmetic, Rows, Cols, RowMajor> 
	Constants<Arithmetic, Rows, Cols, RowMajor, Square>::IDENTITY(Arithmetic(1));
*/

}

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

//


// --- Matrix ---

// -- Matrix Constructors --

// Matrix::Matrix()
//	Generic
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>::Matrix()
:	MatrixMap<Arithmetic, Rows, Cols, RowMajor>()
{
	for (index_t i = 0; i < Rows * Cols; ++i)
		_data[i] = Arithmetic(0);

	_mappedData = _data;
}
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Matrix<Arithmetic, Rows, Rows, RowMajor>::Matrix()
:	MatrixMap<Arithmetic, Rows, Rows, RowMajor>()
{
	for (index_t i = 0; i < Rows * Rows; ++i)
		_data[i] = Arithmetic(0);

	_mappedData = _data;
}
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Matrix<Arithmetic, Rows, 1u, RowMajor>::Matrix()
:	MatrixMap<Arithmetic, Rows, 1u, RowMajor>()
{
	for (index_t i = 0; i < Rows; ++i)
		_data[i] = Arithmetic(0);

	_mappedData = _data;
}
//

// Matrix::Matrix(Arithmetic)
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Matrix<Arithmetic, Rows, Rows, RowMajor>::Matrix(Arithmetic value)
:	MatrixMap<Arithmetic, Rows, Rows, RowMajor>()
{
	for (index_t row = 0; row < Rows; ++row)
	{
		for (index_t col = 0; col < Rows; ++col)
		{
			index_t index = detail::storageIndex<index_t, Rows, Rows, RowMajor>(row, col);
			if (col == row)
				_data[index] = value;
			else
				_data[index] = Arithmetic(0);
		}
	}

	_mappedData = _data;
}
//

// Matrix::Matrix(const Arithmetic*)
//	Generic
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>::Matrix(const Arithmetic* data)
:	MatrixMap<Arithmetic, Rows, Cols, RowMajor>()
{
	std::memcpy(_data, data, sizeof(Arithmetic) * Rows * Cols);
	
	_mappedData = _data;
}
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Matrix<Arithmetic, Rows, Rows, RowMajor>::Matrix(const Arithmetic* data)
:	MatrixMap<Arithmetic, Rows, Rows, RowMajor>()
{
	std::memcpy(_data, data, sizeof(Arithmetic) * Rows * Rows);
	
	_mappedData = _data;
}
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Matrix<Arithmetic, Rows, 1u, RowMajor>::Matrix(const Arithmetic* data)
:	MatrixMap<Arithmetic, Rows, 1u, RowMajor>()
{
	std::memcpy(_data, data, sizeof(Arithmetic) * Rows);
	
	_mappedData = _data;
}
//

// Matrix::Matrix(const Matrix&)
//	Generic
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>::Matrix(const Matrix<Arithmetic, Rows, Cols, RowMajor>& other)
:	MatrixMap<Arithmetic, Rows, Cols, RowMajor>()
{
	std::memcpy(_data, other._data, sizeof(Arithmetic) * Rows * Cols);

	_mappedData = _data;
}
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Matrix<Arithmetic, Rows, Rows, RowMajor>::Matrix(const Matrix<Arithmetic, Rows, Rows, RowMajor>& other)
:	MatrixMap<Arithmetic, Rows, Rows, RowMajor>()
{
	std::memcpy(_data, other._data, sizeof(Arithmetic) * Rows * Rows);

	_mappedData = _data;
}
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Matrix<Arithmetic, Rows, 1u, RowMajor>::Matrix(const Matrix<Arithmetic, Rows, 1u, RowMajor>& other)
:	MatrixMap<Arithmetic, Rows, 1u, RowMajor>()
{
	std::memcpy(_data, other._data, sizeof(Arithmetic) * Rows);

	_mappedData = _data;
}
//

// Matrix::Matrix(std::initializer_list<Arithmetic>)
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Matrix<Arithmetic, Rows, 1u, RowMajor>::Matrix(std::initializer_list<Arithmetic> data)
:	MatrixMap<Arithmetic, Rows, 1u, RowMajor>()
{
	ASSERT(Rows == data.size(), "Too many elements in initializer.");
	
	auto it = data.begin();
	for (index_t i = 0; i < data.size(); ++i)
		_data[i] = *it++;

	_mappedData = _data;
}
//


// -- Matrix Constants --

// ZERO
//	Generic
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
const Matrix<Arithmetic, Rows, Cols, RowMajor> 
	Matrix<Arithmetic, Rows, Cols, RowMajor>::ZERO = Matrix<Arithmetic, Rows, Cols, RowMajor>();
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
const Matrix<Arithmetic, Rows, Rows, RowMajor> 
	Matrix<Arithmetic, Rows, Rows, RowMajor>::ZERO = Matrix<Arithmetic, Rows, Rows, RowMajor>();
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
const Matrix<Arithmetic, Rows, 1u, RowMajor> 
	Matrix<Arithmetic, Rows, 1u, RowMajor>::ZERO = Matrix<Arithmetic, Rows, 1u, RowMajor>();
//

// IDENTITY
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
const Matrix<Arithmetic, Rows, Rows, RowMajor> 
	Matrix<Arithmetic, Rows, Rows, RowMajor>::IDENTITY = Matrix<Arithmetic, Rows, Rows, RowMajor>(Arithmetic(1));
//

// --- MatrixMap ---

// -- MatrixMap Constructors --

// MatrixMap::MatrixMap()
//	Generic
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
MatrixMap<Arithmetic, Rows, Cols, RowMajor>::MatrixMap()
:	_mappedData(nullptr)
{}
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
MatrixMap<Arithmetic, Rows, Rows, RowMajor>::MatrixMap()
:	_mappedData(nullptr)
{}
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
MatrixMap<Arithmetic, Rows, 1u, RowMajor>::MatrixMap()
:	_mappedData(nullptr)
{}
//

// MatrixMap::MatrixMap(Arithmetic*)
//	Generic
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
MatrixMap<Arithmetic, Rows, Cols, RowMajor>::MatrixMap(Arithmetic* data)
:	_mappedData(data)
{}
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
MatrixMap<Arithmetic, Rows, Rows, RowMajor>::MatrixMap(Arithmetic* data)
:	_mappedData(data)
{}
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
MatrixMap<Arithmetic, Rows, 1u, RowMajor>::MatrixMap(Arithmetic* data)
:	_mappedData(data)
{}
//

// MatrixMap::MatrixMap(const MatrixMap&)
//	Generic
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
MatrixMap<Arithmetic, Rows, Cols, RowMajor>::MatrixMap(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other)
:	_mappedData(other._mappedData)
{}
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
MatrixMap<Arithmetic, Rows, Rows, RowMajor>::MatrixMap(const MatrixMap<Arithmetic, Rows, Rows, RowMajor>& other)
:	_mappedData(other._mappedData)
{}
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
MatrixMap<Arithmetic, Rows, 1u, RowMajor>::MatrixMap(const MatrixMap<Arithmetic, Rows, 1u, RowMajor>& other)
:	_mappedData(other._mappedData)
{}
//

// -- Data Access --

// Arithmetic* MatrixMap::data()
//	Generic
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Arithmetic* MatrixMap<Arithmetic, Rows, Cols, RowMajor>::data()
{ return _mappedData; }
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Arithmetic* MatrixMap<Arithmetic, Rows, Rows, RowMajor>::data()
{ return _mappedData; }
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Arithmetic* MatrixMap<Arithmetic, Rows, 1u, RowMajor>::data()
{ return _mappedData; }
//

// const Arithmetic* MatrixMap::data() const
//	Generic
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
const Arithmetic* MatrixMap<Arithmetic, Rows, Cols, RowMajor>::data() const
{ return _mappedData; }
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
const Arithmetic* MatrixMap<Arithmetic, Rows, Rows, RowMajor>::data() const
{ return _mappedData; }
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
const Arithmetic* MatrixMap<Arithmetic, Rows, 1u, RowMajor>::data() const
{ return _mappedData; }
//

// Arithmetic& MatrixMap::operator()(index_t row, index_t col)
//	Generic
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Arithmetic& MatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator()(index_t row, index_t col)
{ return _mappedData[ detail::storageIndex<index_t, Rows, Cols, RowMajor>(row, col) ]; }
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Arithmetic& MatrixMap<Arithmetic, Rows, Rows, RowMajor>::operator()(index_t row, index_t col)
{ return _mappedData[ detail::storageIndex<index_t, Rows, Rows, RowMajor>(row, col) ]; }
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Arithmetic& MatrixMap<Arithmetic, Rows, 1u, RowMajor>::operator()(index_t row, index_t col)
{ return _mappedData[ detail::storageIndex<index_t, Rows, 1u, RowMajor>(row, col) ]; }
//

// const Arithmetic& MatrixMap::operator()(index_t row, index_t col) const
//	Generic
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
const Arithmetic& MatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator()(index_t row, index_t col) const
{ return _mappedData[ detail::storageIndex<index_t, Rows, Cols, RowMajor>(row, col) ]; }
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
const Arithmetic& MatrixMap<Arithmetic, Rows, Rows, RowMajor>::operator()(index_t row, index_t col) const
{ return _mappedData[ detail::storageIndex<index_t, Rows, Rows, RowMajor>(row, col) ]; }
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
const Arithmetic& MatrixMap<Arithmetic, Rows, 1u, RowMajor>::operator()(index_t row, index_t col) const
{ return _mappedData[ detail::storageIndex<index_t, Rows, 1u, RowMajor>(row, col) ]; }
//

// Arithmetic& MatrixMap::operator[](index_t row)
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Arithmetic& MatrixMap<Arithmetic, Rows, 1u, RowMajor>::operator[](index_t row)
{ return _mappedData[row]; }
//

// const Arithmetic& MatrixMap::operator[](index_t row) const
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
const Arithmetic& MatrixMap<Arithmetic, Rows, 1u, RowMajor>::operator[](index_t row) const
{ return _mappedData[row]; }
//


// -- Arithmetics --

// Matrix MatrixMap::operator*(Arithmetic) const
//	Generic
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator*(Arithmetic scalar) const
{
	Arithmetic buffer[Rows * Cols];

	for (index_t i = 0; i < Rows * Cols; ++i)
		buffer[i] = _mappedData[i] * scalar;

	return Matrix<Arithmetic, Rows, Cols, RowMajor>(buffer);
}
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Matrix<Arithmetic, Rows, Rows, RowMajor>
	MatrixMap<Arithmetic, Rows, Rows, RowMajor>::operator*(Arithmetic scalar) const
{
	Arithmetic buffer[Rows * Rows];

	for (index_t i = 0; i < Rows * Rows; ++i)
		buffer[i] = _mappedData[i] * scalar;

	return Matrix<Arithmetic, Rows, Rows, RowMajor>(buffer);
}
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Matrix<Arithmetic, Rows, 1u, RowMajor>
	MatrixMap<Arithmetic, Rows, 1u, RowMajor>::operator*(Arithmetic scalar) const
{
	Arithmetic buffer[Rows];

	for (index_t i = 0; i < Rows; ++i)
		buffer[i] = _mappedData[i] * scalar;

	return Matrix<Arithmetic, Rows, 1u, RowMajor>(buffer);
}
//

// Matrix MatrixMap::operator/(Arithmetic) const
//	Generic
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator/(Arithmetic scalar) const
{
	Arithmetic buffer[Rows * Cols];

	for (index_t i = 0; i < Rows * Cols; ++i)
		buffer[i] = _mappedData[i] / scalar;

	return Matrix<Arithmetic, Rows, Cols, RowMajor>(buffer);
}
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Matrix<Arithmetic, Rows, Rows, RowMajor>
	MatrixMap<Arithmetic, Rows, Rows, RowMajor>::operator/(Arithmetic scalar) const
{
	Arithmetic buffer[Rows * Rows];

	for (index_t i = 0; i < Rows * Rows; ++i)
		buffer[i] = _mappedData[i] / scalar;

	return Matrix<Arithmetic, Rows, Rows, RowMajor>(buffer);
}
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Matrix<Arithmetic, Rows, 1u, RowMajor>
	MatrixMap<Arithmetic, Rows, 1u, RowMajor>::operator/(Arithmetic scalar) const
{
	Arithmetic buffer[Rows];

	for (index_t i = 0; i < Rows; ++i)
		buffer[i] = _mappedData[i] / scalar;

	return Matrix<Arithmetic, Rows, 1u, RowMajor>(buffer);
}
//

// MatrixMap& MatrixMap::operator*=(Arithmetic)
//	Generic
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
MatrixMap<Arithmetic, Rows, Cols, RowMajor>&
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator*=(Arithmetic scalar)
{
	for (index_t i = 0; i < Rows * Cols; ++i)
		_mappedData[i] *= scalar;

	return *this;
}
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
MatrixMap<Arithmetic, Rows, Rows, RowMajor>&
	MatrixMap<Arithmetic, Rows, Rows, RowMajor>::operator*=(Arithmetic scalar)
{
	for (index_t i = 0; i < Rows * Rows; ++i)
		_mappedData[i] *= scalar;

	return *this;
}
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
MatrixMap<Arithmetic, Rows, 1u, RowMajor>&
	MatrixMap<Arithmetic, Rows, 1u, RowMajor>::operator*=(Arithmetic scalar)
{
	for (index_t i = 0; i < Rows; ++i)
		_mappedData[i] *= scalar;

	return *this;
}
//

// MatrixMap& MatrixMap::operator/=(Arithmetic)
//	Generic
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
MatrixMap<Arithmetic, Rows, Cols, RowMajor>&
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator/=(Arithmetic scalar)
{
	for (index_t i = 0; i < Rows * Cols; ++i)
		_mappedData[i] /= scalar;

	return *this;
}
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
MatrixMap<Arithmetic, Rows, Rows, RowMajor>&
	MatrixMap<Arithmetic, Rows, Rows, RowMajor>::operator/=(Arithmetic scalar)
{
	for (index_t i = 0; i < Rows * Rows; ++i)
		_mappedData[i] /= scalar;

	return *this;
}
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
MatrixMap<Arithmetic, Rows, 1u, RowMajor>&
	MatrixMap<Arithmetic, Rows, 1u, RowMajor>::operator/=(Arithmetic scalar)
{
	for (index_t i = 0; i < Rows; ++i)
		_mappedData[i] /= scalar;

	return *this;
}
//

// Matrix MatrixMap::transpose() const
//	Generic
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Cols, Rows, RowMajor>
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>::transpose() const
{
	Matrix<Arithmetic, Cols, Rows, RowMajor> rMat;

	for (index_t row = 0; row < Rows; ++row)
		for (index_t col = 0; col < Cols; ++col)
			rMat(col, row) = 
				_mappedData[ detail::storageIndex<index_t, Rows, Cols, RowMajor>(row, col) ];

	return rMat;
}
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Matrix<Arithmetic, Rows, Rows, RowMajor>
	MatrixMap<Arithmetic, Rows, Rows, RowMajor>::transpose() const
{
	Matrix<Arithmetic, Cols, Rows, RowMajor> rMat;

	for (index_t row = 0; row < Rows; ++row)
		for (index_t col = 0; col < Rows; ++col)
			rMat(col, row) = 
				_mappedData[ detail::storageIndex<index_t, Rows, Rows, RowMajor>(row, col) ];

	return rMat;
}
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Matrix<Arithmetic, 1u, Rows, RowMajor>
	MatrixMap<Arithmetic, Rows, 1u, RowMajor>::transpose() const
{
	Matrix<Arithmetic, 1u, Rows, RowMajor> rMat;

	for (index_t row = 0; row < Rows; ++row)
		rMat(1u, row) = _mappedData[row];

	return rMat;
}
//

// MatrixMap transposeSelf()
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
MatrixMap<Arithmetic, Rows, Rows, RowMajor>&
	MatrixMap<Arithmetic, Rows, Rows, RowMajor>::transposeSelf()
{
	for (index_t row = 0; row < Rows; ++row)
	{
		for (index_t col = row + 1; col < Rows; ++col)
		{
			std::swap(
				_mappedData[ detail::storageIndex<index_t, Rows, Rows, RowMajor>(col, row) ],
				_mappedData[ detail::storageIndex<index_t, Rows, Rows, RowMajor>(row, col) ] );
		}
	}

	return *this;
}
//

// Matrix operator*(const MatrixMap&) const
//	Generic
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
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
template <unsigned int N>
Matrix<Arithmetic, Rows, N, RowMajor>
	MatrixMap<Arithmetic, Rows, Rows, RowMajor>::operator*(const MatrixMap<Arithmetic, Rows, N, RowMajor>& other) const
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
					_mappedData[ detail::storageIndex<index_t, Rows, Rows, RowMajor>(row, k) ]
					* other._mappedData[ detail::storageIndex<index_t, Rows, N, RowMajor>(k, col) ] 
				);
			}
		}
	}

	return Matrix<Arithmetic, Rows, N, RowMajor>(buffer);
}
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
template <unsigned int N>
Matrix<Arithmetic, Rows, N, RowMajor>
	MatrixMap<Arithmetic, Rows, 1u, RowMajor>::operator*(const MatrixMap<Arithmetic, 1u, N, RowMajor>& other) const
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
					_mappedData[ detail::storageIndex<index_t, Rows, 1u, RowMajor>(row, k) ]
					* other._mappedData[ detail::storageIndex<index_t, 1u, N, RowMajor>(k, col) ] 
				);
			}
		}
	}

	return Matrix<Arithmetic, Rows, N, RowMajor>(buffer);
}
//

// MatrixMap& MatrixMap::operator*=(const MatrixMap&)
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
MatrixMap<Arithmetic, Rows, Rows, RowMajor>&
	MatrixMap<Arithmetic, Rows, Rows, RowMajor>::operator*=(const MatrixMap<Arithmetic, Rows, Rows, RowMajor>& other) const
{
	Arithmetic buffer[Rows * Rows];

	for (index_t row = 0; row < Rows; ++row)
	{
		for (index_t col = 0; col < Rows; ++col)
		{
			Arithmetic& value(buffer[ detail::storageIndex<index_t, Rows, Rows, RowMajor>(row, col) ]);
			
			value = Arithmetic(0);
			for (index_t k = 0; k < Rows; ++k)
			{
				value += 
				(
					_mappedData[ detail::storageIndex<index_t, Rows, Rows, RowMajor>(row, k) ]
					* other._mappedData[ detail::storageIndex<index_t, Rows, Rows, RowMajor>(k, col) ] 
				);
			}
		}
	}

	std::memcpy(_mappedData, buffer, Rows * Rows * sizeof(Arithmetic));

	return *this;
}
//

// Arithmetic MatrixMap::length() const
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Arithmetic MatrixMap<Arithmetic, Rows, 1u, RowMajor>::length() const
{
	Arithmetic rVal = Arithmetic(0);

	for (index_t row = 0; row < Rows; ++row)
		rVal += (_mappedData[row] * _mappedData[row]);

	return std::sqrt(rVal);
}
//

// Arithmetic MatrixMap::lengthSquared() const
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Arithmetic MatrixMap<Arithmetic, Rows, 1u, RowMajor>::lengthSquared() const
{
	Arithmetic rVal = Arithmetic(0);

	for (index_t row = 0; row < Rows; ++row)
		rVal += (_mappedData[row] * _mappedData[row]);

	return rVal;
}
//


// -- Comparators --

// bool MatrixMap::operator==(const MatrixMap&) const
//	Generic
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
bool MatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator==(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other) const
{
	for (index_t i = 0; i < Rows * Cols; ++i)
		if (_mappedData[i] != other._mappedData[i])
			return false;
	
	return true;
}
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
bool MatrixMap<Arithmetic, Rows, Rows, RowMajor>::operator==(const MatrixMap<Arithmetic, Rows, Rows, RowMajor>& other) const
{
	for (index_t i = 0; i < Rows * Rows; ++i)
		if (_mappedData[i] != other._mappedData[i])
			return false;
	
	return true;
}
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
bool MatrixMap<Arithmetic, Rows, 1u, RowMajor>::operator==(const MatrixMap<Arithmetic, Rows, 1u, RowMajor>& other) const
{
	for (index_t i = 0; i < Rows; ++i)
		if (_mappedData[i] != other._mappedData[i])
			return false;
	
	return true;
}
//

// bool MatrixMap::operator!=(const MatrixMap&) const
//	Generic
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
bool MatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator!=(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other) const
{ return !(*this == other); }
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
bool MatrixMap<Arithmetic, Rows, Rows, RowMajor>::operator!=(const MatrixMap<Arithmetic, Rows, Rows, RowMajor>& other) const
{ return !(*this == other); }
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
bool MatrixMap<Arithmetic, Rows, 1u, RowMajor>::operator!=(const MatrixMap<Arithmetic, Rows, 1u, RowMajor>& other) const
{ return !(*this == other); }
//

}