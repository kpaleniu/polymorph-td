#include "math/Matrix.hpp"

#include <Assert.hpp>
#include <memory>
#include <cmath>

namespace math {


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

// --- Matrix ---

// -- Constants --

template <MATRIX_TEMPLATES_DECLARATION>
const Matrix<MATRIX_TEMPLATES> Matrix<MATRIX_TEMPLATES>::ZERO = Matrix<MATRIX_TEMPLATES>();

template <MATRIX_SQUARE_TEMPLATES_DECLARATION>
const Matrix<MATRIX_SQUARE_TEMPLATES> Matrix<MATRIX_SQUARE_TEMPLATES>::ZERO = Matrix<MATRIX_SQUARE_TEMPLATES>();

template <MATRIX_SQUARE_TEMPLATES_DECLARATION>
const Matrix<MATRIX_SQUARE_TEMPLATES> Matrix<MATRIX_SQUARE_TEMPLATES>::IDENTITY = Matrix<MATRIX_SQUARE_TEMPLATES>(1);

template <MATRIX_COLUMN_TEMPLATES_DECLARATION>
const Matrix<MATRIX_COLUMN_TEMPLATES> Matrix<MATRIX_COLUMN_TEMPLATES>::ZERO = Matrix<MATRIX_COLUMN_TEMPLATES>();


// -- Matrix implicit operators overwriting --


// Matrix::Matrix()

template <MATRIX_TEMPLATES_DECLARATION>
Matrix<MATRIX_TEMPLATES>::Matrix()
:	MatrixMap<MATRIX_TEMPLATES>()
{
	for (index_t i = 0; i < this->rows() * this->cols(); ++i)
		_data[i] = Arithmetic(0);

	this->_mappedData = _data;
}
template <MATRIX_SQUARE_TEMPLATES_DECLARATION>
Matrix<MATRIX_SQUARE_TEMPLATES>::Matrix()
	: MatrixMap<MATRIX_SQUARE_TEMPLATES>()
{
	for (index_t i = 0; i < this->rows() * this->cols(); ++i)
		_data[i] = Arithmetic(0);

	this->_mappedData = _data;
}
template <MATRIX_COLUMN_TEMPLATES_DECLARATION>
Matrix<MATRIX_COLUMN_TEMPLATES>::Matrix()
	: MatrixMap<MATRIX_COLUMN_TEMPLATES>()
{
	for (index_t i = 0; i < this->rows() * this->cols(); ++i)
		_data[i] = Arithmetic(0);

	this->_mappedData = _data;
}


// Matrix::Matrix(const Matrix&)

template <MATRIX_TEMPLATES_DECLARATION>
Matrix<MATRIX_TEMPLATES>::Matrix(const Matrix<MATRIX_TEMPLATES>& other)
:	 MatrixMap<MATRIX_TEMPLATES>()
{
	for (index_t i = 0; i < this->rows() * this->cols(); ++i)
		_data[i] = other._data[i];

	this->_mappedData = _data;
}
template <MATRIX_SQUARE_TEMPLATES_DECLARATION>
Matrix<MATRIX_SQUARE_TEMPLATES>::Matrix(const Matrix<MATRIX_SQUARE_TEMPLATES>& other)
:	 MatrixMap<MATRIX_SQUARE_TEMPLATES>()
{
	for (index_t i = 0; i < this->rows() * this->cols(); ++i)
		_data[i] = other._data[i];

	this->_mappedData = _data;
}
template <MATRIX_COLUMN_TEMPLATES_DECLARATION>
Matrix<MATRIX_COLUMN_TEMPLATES>::Matrix(const Matrix<MATRIX_COLUMN_TEMPLATES>& other)
:	 MatrixMap<MATRIX_COLUMN_TEMPLATES>()
{
	for (index_t i = 0; i < this->rows() * this->cols(); ++i)
		_data[i] = other._data[i];

	this->_mappedData = _data;
}

// Matrix& Matrix::operator=(const Matrix&)

template <MATRIX_TEMPLATES_DECLARATION>
Matrix<MATRIX_TEMPLATES>&
	Matrix<MATRIX_TEMPLATES>::operator=(
		const Matrix<MATRIX_TEMPLATES>& other)
{
	return *this = static_cast<const MatrixMap<MATRIX_TEMPLATES>&>(other);
}
template <MATRIX_SQUARE_TEMPLATES_DECLARATION>
Matrix<MATRIX_SQUARE_TEMPLATES>&
	Matrix<MATRIX_SQUARE_TEMPLATES>::operator=(
		const Matrix<MATRIX_SQUARE_TEMPLATES>& other)
{
	return *this = static_cast<const MatrixMap<MATRIX_SQUARE_TEMPLATES>&>(other);
}
template <MATRIX_COLUMN_TEMPLATES_DECLARATION>
Matrix<MATRIX_COLUMN_TEMPLATES>&
	Matrix<MATRIX_COLUMN_TEMPLATES>::operator=(
		const Matrix<MATRIX_COLUMN_TEMPLATES>& other)
{
	return *this = static_cast<const MatrixMap<MATRIX_COLUMN_TEMPLATES>&>(other);
}


// -- Matrix additional constructors --

// Matrix::Matrix(const MatrixMap&)

template <MATRIX_TEMPLATES_DECLARATION>
Matrix<MATRIX_TEMPLATES>::Matrix(const MatrixMap<MATRIX_TEMPLATES>& other)
	: MatrixMap<MATRIX_TEMPLATES>()
{
	for (index_t i = 0; i < this->rows() * this->cols(); ++i)
		_data[i] = other._mappedData[i];

	this->_mappedData = _data;
}
template <MATRIX_SQUARE_TEMPLATES_DECLARATION>
Matrix<MATRIX_SQUARE_TEMPLATES>::Matrix(const MatrixMap<MATRIX_SQUARE_TEMPLATES>& other)
	: MatrixMap<MATRIX_SQUARE_TEMPLATES>()
{
	for (index_t i = 0; i < this->rows() * this->cols(); ++i)
		_data[i] = other._mappedData[i];

	this->_mappedData = _data;
}
template <MATRIX_COLUMN_TEMPLATES_DECLARATION>
Matrix<MATRIX_COLUMN_TEMPLATES>::Matrix(const MatrixMap<MATRIX_COLUMN_TEMPLATES>& other)
	: MatrixMap<MATRIX_COLUMN_TEMPLATES>()
{
	for (index_t i = 0; i < this->rows() * this->cols(); ++i)
		_data[i] = other._mappedData[i];

	this->_mappedData = _data;
}


// Matrix::Matrix(const Arithmetic*)

template <MATRIX_TEMPLATES_DECLARATION>
Matrix<MATRIX_TEMPLATES>::Matrix(const Arithmetic* data)
	: MatrixMap<MATRIX_TEMPLATES>()
{
	for (index_t i = 0; i < this->rows() * this->cols(); ++i)
		_data[i] = data[i];

	this->_mappedData = _data;
}
template <MATRIX_SQUARE_TEMPLATES_DECLARATION>
Matrix<MATRIX_SQUARE_TEMPLATES>::Matrix(const Arithmetic* data)
	: MatrixMap<MATRIX_SQUARE_TEMPLATES>()
{
	for (index_t i = 0; i < this->rows() * this->cols(); ++i)
		_data[i] = data[i];

	this->_mappedData = _data;
}
template <MATRIX_COLUMN_TEMPLATES_DECLARATION>
Matrix<MATRIX_COLUMN_TEMPLATES>::Matrix(const Arithmetic* data)
	: MatrixMap<MATRIX_COLUMN_TEMPLATES>()
{
	for (index_t i = 0; i < this->rows() * this->cols(); ++i)
		_data[i] = data[i];

	this->_mappedData = _data;
}


// Matrix::Matrix(Arithmetic)  -- SQUARE ONLY --

template <MATRIX_SQUARE_TEMPLATES_DECLARATION>
Matrix<MATRIX_SQUARE_TEMPLATES>::Matrix(Arithmetic s)
{
	for (index_t j = 0; j < this->rows(); ++j)
	{
		for (index_t i = 0; i < this->cols(); ++i)
		{
			if (i == j)
				_data[j * this->rows() + i] = s;
			else
				_data[j * this->rows() + i] = 0;
		}
	}
	
	this->_mappedData = _data;
}


// Matrix::Matrix(const std::initializer_list<Arithmetic>&)  -- VECTOR ONLY --

template <MATRIX_COLUMN_TEMPLATES_DECLARATION>
Matrix<MATRIX_COLUMN_TEMPLATES>::Matrix(const std::initializer_list<Arithmetic>& data)
{
	// TODO When C++14 is supported, use static_assert.
	ASSERT(data.size() == Rows, "Initializer list size is bad.");

	auto it = data.begin();
	for (index_t i = 0; i < this->rows(); ++i)
		_data[i] = *it++;

	this->_mappedData = _data;
}


// -- Matrix additional methods --


// Matrix& Matrix::operator=(const MatrixMap&)

template <MATRIX_TEMPLATES_DECLARATION>
Matrix<MATRIX_TEMPLATES>& Matrix<MATRIX_TEMPLATES>::operator=(
	const MatrixMap<MATRIX_TEMPLATES>& other)
{
	static_cast<MatrixMap<MATRIX_TEMPLATES>&>(*this) = other;

	return *this;
}

template <MATRIX_SQUARE_TEMPLATES_DECLARATION>
Matrix<MATRIX_SQUARE_TEMPLATES>& Matrix<MATRIX_SQUARE_TEMPLATES>::operator=(
	const MatrixMap<MATRIX_SQUARE_TEMPLATES>& other)
{
	static_cast<MatrixMap<MATRIX_SQUARE_TEMPLATES>&>(*this) = other;

	return *this;
}

template <MATRIX_COLUMN_TEMPLATES_DECLARATION>
Matrix<MATRIX_COLUMN_TEMPLATES>& Matrix<MATRIX_COLUMN_TEMPLATES>::operator=(
	const MatrixMap<MATRIX_COLUMN_TEMPLATES>& other)
{
	static_cast<MatrixMap<MATRIX_COLUMN_TEMPLATES>&>(*this) = other;

	return *this;
}

}


#undef MATRIX_TEMPLATES_DECLARATION
#undef MATRIX_TEMPLATES
#undef MATRIX_SQUARE_TEMPLATES_DECLARATION
#undef MATRIX_SQUARE_TEMPLATES
#undef MATRIX_COLUMN_TEMPLATES_DECLARATION
#undef MATRIX_COLUMN_TEMPLATES
