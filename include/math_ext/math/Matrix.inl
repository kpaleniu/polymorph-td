#include "math/Matrix.hpp"

#include <Assert.hpp>
#include <memory>
#include <cmath>

namespace math {

namespace detail {

template <typename Index, bool RowMajor>
Index storageIndex(unsigned int rows, unsigned int cols, Index row, Index col)
{
	return (RowMajor ? (row * cols + col) : (col * rows + row));
}

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

	this->_mappedData = _data;
}
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Matrix<Arithmetic, Rows, Rows, RowMajor>::Matrix()
:	MatrixMap<Arithmetic, Rows, Rows, RowMajor>()
{
	for (index_t i = 0; i < Rows * Rows; ++i)
		_data[i] = Arithmetic(0);

	this->_mappedData = _data;
}
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Matrix<Arithmetic, Rows, 1u, RowMajor>::Matrix()
:	MatrixMap<Arithmetic, Rows, 1u, RowMajor>()
{
	for (index_t i = 0; i < Rows; ++i)
		_data[i] = Arithmetic(0);

	this->_mappedData = _data;
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
			index_t index = detail::storageIndex<index_t, RowMajor>(Rows, Rows, row, col);
			if (col == row)
				_data[index] = value;
			else
				_data[index] = Arithmetic(0);
		}
	}

	this->_mappedData = _data;
}
//

// Matrix::Matrix(const Arithmetic*)
//	Generic
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>::Matrix(const Arithmetic* data)
:	MatrixMap<Arithmetic, Rows, Cols, RowMajor>()
{
	std::memcpy(_data, data, sizeof(Arithmetic) * Rows * Cols);
	
	this->_mappedData = _data;
}
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Matrix<Arithmetic, Rows, Rows, RowMajor>::Matrix(const Arithmetic* data)
:	MatrixMap<Arithmetic, Rows, Rows, RowMajor>()
{
	std::memcpy(_data, data, sizeof(Arithmetic) * Rows * Rows);
	
	this->_mappedData = _data;
}
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Matrix<Arithmetic, Rows, 1u, RowMajor>::Matrix(const Arithmetic* data)
:	MatrixMap<Arithmetic, Rows, 1u, RowMajor>()
{
	std::memcpy(_data, data, sizeof(Arithmetic) * Rows);
	
	this->_mappedData = _data;
}
//

// Matrix::Matrix(const Matrix&)
//	Generic
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>::Matrix(const Matrix<Arithmetic, Rows, Cols, RowMajor>& other)
:	MatrixMap<Arithmetic, Rows, Cols, RowMajor>()
{
	std::memcpy(_data, other._mappedData, sizeof(Arithmetic) * Rows * Cols);

	this->_mappedData = _data;
}
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Matrix<Arithmetic, Rows, Rows, RowMajor>::Matrix(const Matrix<Arithmetic, Rows, Rows, RowMajor>& other)
:	MatrixMap<Arithmetic, Rows, Rows, RowMajor>()
{
	std::memcpy(_data, other._mappedData, sizeof(Arithmetic) * Rows * Rows);

	this->_mappedData = _data;
}
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Matrix<Arithmetic, Rows, 1u, RowMajor>::Matrix(const Matrix<Arithmetic, Rows, 1u, RowMajor>& other)
:	MatrixMap<Arithmetic, Rows, 1u, RowMajor>()
{
	std::memcpy(_data, other._mappedData, sizeof(Arithmetic) * Rows);

	this->_mappedData = _data;
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

	this->_mappedData = _data;
}
//

// Matrix& Matrix::operator=(const Matrix&)
//	Generic
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>& 
	Matrix<Arithmetic, Rows, Cols, RowMajor>::operator=(const Matrix<Arithmetic, Rows, Cols, RowMajor>& other)
{
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator=(other);
	return *this;
}
//	Square
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Matrix<Arithmetic, Rows, Rows, RowMajor>& 
	Matrix<Arithmetic, Rows, Rows, RowMajor>::operator=(const Matrix<Arithmetic, Rows, Rows, RowMajor>& other)
{
	MatrixMap<Arithmetic, Rows, Rows, RowMajor>::operator=(other);
	return *this;
}
//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Matrix<Arithmetic, Rows, 1u, RowMajor>& 
	Matrix<Arithmetic, Rows, 1u, RowMajor>::operator=(const Matrix<Arithmetic, Rows, 1u, RowMajor>& other)
{
	MatrixMap<Arithmetic, Rows, 1u, RowMajor>::operator=(other);
	return *this;
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

// ----- CommonMatrixMap -----

namespace detail {

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>::CommonMatrixMap(Arithmetic* data)
:	_mappedData(data)
{
}
template <typename Arithmetic, bool RowMajor>
CommonMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>::CommonMatrixMap(Arithmetic* data, size_t rows)
:	_mappedData(data), _rows(rows)
{
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Arithmetic* 
	CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>::data()
{
	return _mappedData;
}
template <typename Arithmetic, bool RowMajor>
Arithmetic* 
	CommonMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>::data()
{
	return _mappedData;
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
const Arithmetic* 
	CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>::data() const
{
	return _mappedData;
}
template <typename Arithmetic, bool RowMajor>
const Arithmetic* 
	CommonMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>::data() const
{
	return _mappedData;
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Arithmetic& 
	CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator()(index_t row, index_t col)
{ 
	return _mappedData[ detail::storageIndex<index_t, RowMajor>(Rows, Cols, row, col) ];
}
template <typename Arithmetic, bool RowMajor>
Arithmetic& 
	CommonMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>::operator()(index_t row, index_t col)
{ 
	return _mappedData[ detail::storageIndex<index_t, RowMajor>(_rows, this->Cols, row, col) ];
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
const Arithmetic& 
	CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator()(index_t row, index_t col) const
{ 
	return _mappedData[ detail::storageIndex<index_t, RowMajor>(Rows, Cols, row, col) ];
}
template <typename Arithmetic, bool RowMajor>
const Arithmetic& 
	CommonMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>::operator()(index_t row, index_t col) const
{ 
	return _mappedData[ detail::storageIndex<index_t, RowMajor>(_rows, this->Cols, row, col) ];
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>
	CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator*(Arithmetic scalar) const
{
	Arithmetic buffer[Rows * Cols];

	for (index_t i = 0; i < Rows * Cols; ++i)
		buffer[i] = _mappedData[i] * scalar;

	return Matrix<Arithmetic, Rows, Cols, RowMajor>(buffer);
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>
	CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator/(Arithmetic scalar) const
{
	Arithmetic buffer[Rows * Cols];

	for (index_t i = 0; i < Rows * Cols; ++i)
		buffer[i] = _mappedData[i] / scalar;

	return Matrix<Arithmetic, Rows, Cols, RowMajor>(buffer);
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
MatrixMap<Arithmetic, Rows, Cols, RowMajor>&
	CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator*=(Arithmetic scalar)
{
	for (index_t i = 0; i < Rows * Cols; ++i)
		_mappedData[i] *= scalar;

	return *static_cast<MatrixMap<Arithmetic, Rows, Cols, RowMajor>*>(this);
}
template <typename Arithmetic, bool RowMajor>
MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>&
	CommonMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>::operator*=(Arithmetic scalar)
{
	for (index_t i = 0; i < _rows * this->Cols; ++i)
		_mappedData[i] *= scalar;

	return *static_cast<MatrixMap<Arithmetic, DYNAMIC, this->Cols, RowMajor>*>(this);
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
MatrixMap<Arithmetic, Rows, Cols, RowMajor>&
	CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator/=(Arithmetic scalar)
{
	for (index_t i = 0; i < Rows * Cols; ++i)
		_mappedData[i] /= scalar;

	return *static_cast<MatrixMap<Arithmetic, Rows, Cols, RowMajor>*>(this);
}
template <typename Arithmetic, bool RowMajor>
MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>&
	CommonMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>::operator/=(Arithmetic scalar)
{
	for (index_t i = 0; i < _rows; ++i)
		_mappedData[i] /= scalar;

	return *static_cast<MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>*>(this);
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>
	CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator+(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other) const
{
	Matrix<Arithmetic, Rows, Cols, RowMajor> rMat;

	for (index_t row = 0; row < Rows; ++row)
	{
		for (index_t col = 0; col < Cols; ++col)
		{
			rMat._mappedData[ detail::storageIndex<index_t, RowMajor>(Rows, Cols, row, col) ] = 
				_mappedData[ detail::storageIndex<index_t, RowMajor>(Rows, Cols, row, col) ]
				+ other._mappedData[ detail::storageIndex<index_t, RowMajor>(Rows, Cols, row, col) ];
		}
	}

	return rMat;
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Rows, Cols, RowMajor>
	CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator-(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other) const
{
	Matrix<Arithmetic, Rows, Cols, RowMajor> rMat;

	for (index_t row = 0; row < Rows; ++row)
	{
		for (index_t col = 0; col < Cols; ++col)
		{
			rMat._mappedData[ detail::storageIndex<index_t, RowMajor>(Rows, Cols, row, col) ] = 
				_mappedData[ detail::storageIndex<index_t, RowMajor>(Rows, Cols, row, col) ]
				- other._mappedData[ detail::storageIndex<index_t, RowMajor>(Rows, Cols, row, col) ];
		}
	}

	return rMat;
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
MatrixMap<Arithmetic, Rows, Cols, RowMajor>&
	CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator+=(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other)
{
	for (index_t row = 0; row < Rows; ++row)
	{
		for (index_t col = 0; col < Cols; ++col)
		{
			_mappedData[ detail::storageIndex<index_t, RowMajor>(Rows, Cols, row, col) ] +=
				other._mappedData[ detail::storageIndex<index_t, RowMajor>(Rows, Cols, row, col) ];
		}
	}

	return *static_cast<MatrixMap<Arithmetic, Rows, Cols, RowMajor>*>(this);
}
template <typename Arithmetic, bool RowMajor>
MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>&
	CommonMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>::operator+=(const MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>& other)
{
	ASSERT(_rows == other._rows, "Arithmetics with different vector types forbidden.");

	for (index_t row = 0; row < _rows; ++row)
		_mappedData[row] += other._mappedData[row];

	return *static_cast<MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>*>(this);
}
template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
MatrixMap<Arithmetic, Rows, Cols, RowMajor>&
	CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator-=(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other)
{
	for (index_t row = 0; row < Rows; ++row)
	{
		for (index_t col = 0; col < Cols; ++col)
		{
			_mappedData[ detail::storageIndex<index_t, RowMajor>(Rows, Cols, row, col) ] -=
				other._mappedData[ detail::storageIndex<index_t, RowMajor>(Rows, Cols, row, col) ];
		}
	}

	return *static_cast<MatrixMap<Arithmetic, Rows, Cols, RowMajor>*>(this);
}
template <typename Arithmetic, bool RowMajor>
MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>&
	CommonMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>::operator-=(const MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>& other)
{
	ASSERT(_rows == other._rows, "Arithmetics with different vector types forbidden.");

	for (index_t row = 0; row < _rows; ++row)
		_mappedData[row] -= other._mappedData[row];

	return *static_cast<MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>*>(this);
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>&
	CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator=(const CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>& other)
{
	for (index_t i = 0; i < Rows * Cols; ++i)
		_mappedData[i] = other._mappedData[i];

	return *this;
}
template <typename Arithmetic, bool RowMajor>
CommonMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>&
	CommonMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>::operator=(const CommonMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>& other)
{
	ASSERT(_rows == other._rows, "Trying to assign dynamic vector with other size.");

	for (index_t i = 0; i < _rows; ++i)
		_mappedData[i] = other._mappedData[i];

	return *this;
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
Matrix<Arithmetic, Cols, Rows, RowMajor>
	CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>::transpose() const
{
	Matrix<Arithmetic, Cols, Rows, RowMajor> rMat;

	for (index_t row = 0; row < Rows; ++row)
		for (index_t col = 0; col < Cols; ++col)
			rMat(col, row) = 
				_mappedData[ detail::storageIndex<index_t, RowMajor>(Rows, Cols, row, col) ];

	return rMat;
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
template <unsigned int N>
Matrix<Arithmetic, Rows, N, RowMajor>
	CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator*(const MatrixMap<Arithmetic, Cols, N, RowMajor>& other) const
{
	Arithmetic buffer[Rows * N];

	for (index_t row = 0; row < Rows; ++row)
	{
		for (index_t col = 0; col < N; ++col)
		{
			Arithmetic& value(buffer[ detail::storageIndex<index_t, RowMajor>(Rows, N, row, col) ]);
			
			value = Arithmetic(0);

			for (index_t k = 0; k < Rows; ++k)
			{
				value +=
				(
					_mappedData[ detail::storageIndex<index_t, RowMajor>(Rows, Cols, row, k) ]
					* other._mappedData[ detail::storageIndex<index_t, RowMajor>(Cols, N, k, col) ]
				);
			}
		}
	}

	return Matrix<Arithmetic, Rows, N, RowMajor>(buffer);
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
bool CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator==(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other) const
{
	for (index_t i = 0; i < Rows * Cols; ++i)
		if (_mappedData[i] != other._mappedData[i])
			return false;
	
	return true;
}
template <typename Arithmetic, bool RowMajor>
bool CommonMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>::operator==(const MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>& other) const
{
	ASSERT(_rows == other._rows, "Trying to assign dynamic vector with other size.");
	for (index_t i = 0; i < _rows; ++i)
		if (_mappedData[i] != other._mappedData[i])
			return false;
	
	return true;
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
bool CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator!=(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other) const
{ 
	return !(*this == other); 
}
template <typename Arithmetic, bool RowMajor>
bool CommonMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>::operator!=(const MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>& other) const
{ 
	return !(*this == other); 
}

} /* namespace detail */

// --- MatrixMap Generic ---

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
MatrixMap<Arithmetic, Rows, Cols, RowMajor>::MatrixMap()
:	detail::CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>(nullptr)
{}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
MatrixMap<Arithmetic, Rows, Cols, RowMajor>::MatrixMap(Arithmetic* data)
:	detail::CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>(data)
{}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
MatrixMap<Arithmetic, Rows, Cols, RowMajor>&
	MatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator=(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other)
{
	detail::CommonMatrixMap<Arithmetic, Rows, Cols, RowMajor>::operator=(other);
	return *this;
}

// --- MatrixMap Square ---

template <typename Arithmetic, unsigned int Rows, bool RowMajor>
MatrixMap<Arithmetic, Rows, Rows, RowMajor>::MatrixMap()
:	detail::CommonMatrixMap<Arithmetic, Rows, Rows, RowMajor>(nullptr)
{}

template <typename Arithmetic, unsigned int Rows, bool RowMajor>
MatrixMap<Arithmetic, Rows, Rows, RowMajor>::MatrixMap(Arithmetic* data)
:	detail::CommonMatrixMap<Arithmetic, Rows, Rows, RowMajor>(data)
{}

template <typename Arithmetic, unsigned int Rows, bool RowMajor>
MatrixMap<Arithmetic, Rows, Rows, RowMajor>&
	MatrixMap<Arithmetic, Rows, Rows, RowMajor>::transposeSelf()
{
    typedef typename Matrix<Arithmetic, Rows, Rows, RowMajor>::index_t index_t;

	for (index_t row = 0; row < Rows; ++row)
	{
		for (index_t col = row + 1; col < Rows; ++col)
		{
			std::swap(
				this->_mappedData[ detail::storageIndex<index_t, RowMajor>(Rows, Rows, col, row) ],
				this->_mappedData[ detail::storageIndex<index_t, RowMajor>(Rows, Rows, row, col) ] );
		}
	}

	return *this;
}

template <typename Arithmetic, unsigned int Rows, bool RowMajor>
MatrixMap<Arithmetic, Rows, Rows, RowMajor>&
	MatrixMap<Arithmetic, Rows, Rows, RowMajor>::operator*=(const MatrixMap<Arithmetic, Rows, Rows, RowMajor>& other)
{
	Arithmetic buffer[Rows * Rows];
    typedef typename Matrix<Arithmetic, Rows, Rows, RowMajor>::index_t index_t;

	for (index_t row = 0; row < Rows; ++row)
	{
		for (index_t col = 0; col < Rows; ++col)
		{
			Arithmetic& value(buffer[ detail::storageIndex<index_t, RowMajor>(Rows, Rows, row, col) ]);
			
			value = Arithmetic(0);
			for (index_t k = 0; k < Rows; ++k)
			{
				value += 
				(
					this->_mappedData[ detail::storageIndex<index_t, RowMajor>(Rows, Rows, row, k) ]
					* other._mappedData[ detail::storageIndex<index_t, RowMajor>(Rows, Rows, k, col) ] 
				);
			}
		}
	}

	std::memcpy(this->_mappedData, buffer, Rows * Rows * sizeof(Arithmetic));

	return *this;
}

template <typename Arithmetic, unsigned int Rows, bool RowMajor>
MatrixMap<Arithmetic, Rows, Rows, RowMajor>&
	MatrixMap<Arithmetic, Rows, Rows, RowMajor>::operator=(const MatrixMap<Arithmetic, Rows, Rows, RowMajor>& other)
{
	detail::CommonMatrixMap<Arithmetic, Rows, Rows, RowMajor>::operator=(other);
	return *this;
}


// --- MatrixMap Vector ---

//	Vector
template <typename Arithmetic, unsigned int Rows, bool RowMajor>
MatrixMap<Arithmetic, Rows, 1u, RowMajor>::MatrixMap()
:	detail::CommonMatrixMap<Arithmetic, Rows, 1u, RowMajor>(nullptr)
{}

template <typename Arithmetic, unsigned int Rows, bool RowMajor>
MatrixMap<Arithmetic, Rows, 1u, RowMajor>::MatrixMap(Arithmetic* data)
:	detail::CommonMatrixMap<Arithmetic, Rows, 1u, RowMajor>(data)
{}

template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Arithmetic& MatrixMap<Arithmetic, Rows, 1u, RowMajor>::operator[](index_t row)
{ 
	ASSERT(row < Rows, "Index out of bounds.");
	return this->_mappedData[row]; 
}

template <typename Arithmetic, unsigned int Rows, bool RowMajor>
const Arithmetic& MatrixMap<Arithmetic, Rows, 1u, RowMajor>::operator[](index_t row) const
{ 
	ASSERT(row < Rows, "Index out of bounds.");
	return this->_mappedData[row]; 
}

template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Arithmetic MatrixMap<Arithmetic, Rows, 1u, RowMajor>::length() const
{
	Arithmetic rVal = Arithmetic(0);

	for (index_t row = 0; row < Rows; ++row)
		rVal += (this->_mappedData[row] * this->_mappedData[row]);

	return std::sqrt(rVal);
}

template <typename Arithmetic, unsigned int Rows, bool RowMajor>
Arithmetic MatrixMap<Arithmetic, Rows, 1u, RowMajor>::lengthSquared() const
{
	Arithmetic rVal = Arithmetic(0);

	for (index_t row = 0; row < Rows; ++row)
		rVal += (this->_mappedData[row] * this->_mappedData[row]);

	return rVal;
}

template <typename Arithmetic, unsigned int Rows, bool RowMajor>
MatrixMap<Arithmetic, Rows, 1u, RowMajor>&
	MatrixMap<Arithmetic, Rows, 1u, RowMajor>::operator=(const MatrixMap<Arithmetic, Rows, 1u, RowMajor>& other)
{
	detail::CommonMatrixMap<Arithmetic, Rows, 1u, RowMajor>::operator=(other);
	return *this;
}


// --- MatrixMap Dynamic Vector ---

template <typename Arithmetic, bool RowMajor>
MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>::MatrixMap()
:	detail::CommonMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>(nullptr, 0u)
{}

/*
template <typename Arithmetic, bool RowMajor>
MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>::MatrixMap(Arithmetic* data, index_t size)
:	detail::CommonMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>(data, size)
{}
*/

template <typename Arithmetic, bool RowMajor>
Arithmetic& MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>::operator[](index_t row)
{ 
	ASSERT(row < this->_rows, "Index out of bounds.");
	return this->_mappedData[row]; 
}

template <typename Arithmetic, bool RowMajor>
const Arithmetic& MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>::operator[](index_t row) const
{ 
	ASSERT(row < this->_rows, "Index out of bounds.");
	return this->_mappedData[row]; 
}

template <typename Arithmetic, bool RowMajor>
Arithmetic MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>::length() const
{
	Arithmetic rVal = Arithmetic(0);

	for (index_t row = 0; row < this->_rows; ++row)
		rVal += (this->_mappedData[row] * this->_mappedData[row]);

	return std::sqrt(rVal);
}

template <typename Arithmetic, bool RowMajor>
Arithmetic MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>::lengthSquared() const
{
	Arithmetic rVal = Arithmetic(0);

	for (index_t row = 0; row < this->_rows; ++row)
		rVal += (this->_mappedData[row] * this->_mappedData[row]);

	return rVal;
}

template <typename Arithmetic, bool RowMajor>
size_t
	MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>::rows() const
{
	return this->_rows;
}

template <typename Arithmetic, bool RowMajor>
MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>&
	MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>::operator=(const MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>& other)
{
	detail::CommonMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>::operator=(other);
	return *this;
}

}