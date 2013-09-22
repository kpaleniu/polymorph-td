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

#include "math/types.hpp"

#include <Assert.hpp>

namespace math {

namespace detail {

template <bool RowMajor>
index_t storageIndex(unsigned int rows, unsigned int cols, index_t row, index_t col)
{
	return (RowMajor ? (row * cols + col) : (col * rows + row));
}


template <MATRIX_TEMPLATES_DECLARATION>
BaseMatrixMap<MATRIX_TEMPLATES>::BaseMatrixMap(Arithmetic* data)
:	_mappedData(data)
{
}

template <MATRIX_TEMPLATES_DECLARATION>
Arithmetic* BaseMatrixMap<MATRIX_TEMPLATES>::data()
{
	return _mappedData;
}
template <MATRIX_TEMPLATES_DECLARATION>
const Arithmetic* BaseMatrixMap<MATRIX_TEMPLATES>::data() const
{
	return _mappedData;
}

template <MATRIX_TEMPLATES_DECLARATION>
Arithmetic& BaseMatrixMap<MATRIX_TEMPLATES>::operator()(index_t row, index_t col)
{
	return _mappedData[detail::storageIndex<RowMajor>(Rows, Cols, row, col)];
}

template <MATRIX_TEMPLATES_DECLARATION>
const Arithmetic& BaseMatrixMap<MATRIX_TEMPLATES>::operator()(index_t row, index_t col) const
{
	return _mappedData[detail::storageIndex<RowMajor>(Rows, Cols, row, col)];
}

}


// --- MatrixMap ---

template <MATRIX_TEMPLATES_DECLARATION>
MatrixMap<MATRIX_TEMPLATES>::MatrixMap(Arithmetic* data)
:	detail::BaseMatrixMap<MATRIX_TEMPLATES>(data)
{
}

template <MATRIX_TEMPLATES_DECLARATION>
MatrixMap<MATRIX_TEMPLATES>& MatrixMap<MATRIX_TEMPLATES>::operator=(
	const MatrixMap<MATRIX_TEMPLATES>& other)
{
	for (index_t i = 0; i < this->rows() * this->cols(); ++i)
		this->_mappedData[i] = other._mappedData[i];

	return *this;
}

// --- MatrixMap Vector ---

template <MATRIX_COLUMN_TEMPLATES_DECLARATION>
MatrixMap<MATRIX_COLUMN_TEMPLATES>::MatrixMap(Arithmetic* data)
:	detail::BaseMatrixMap<MATRIX_COLUMN_TEMPLATES>(data)
{
}
template <MATRIX_COLUMN_DYNAMIC_TEMPLATES_DECLARATION>
MatrixMap<MATRIX_COLUMN_DYNAMIC_TEMPLATES>::MatrixMap(Arithmetic* data, unsigned int rows)
	: detail::BaseMatrixMap<MATRIX_COLUMN_DYNAMIC_TEMPLATES>(data)
{
	this->_rows = rows;
}

template <MATRIX_COLUMN_TEMPLATES_DECLARATION>
MatrixMap<MATRIX_COLUMN_TEMPLATES>& MatrixMap<MATRIX_COLUMN_TEMPLATES>::operator=(
	const MatrixMap<MATRIX_COLUMN_TEMPLATES>& other)
{
	for (index_t i = 0; i < this->rows() * this->cols(); ++i)
		this->_mappedData[i] = other._mappedData[i];

	return *this;
}
template <MATRIX_COLUMN_DYNAMIC_TEMPLATES_DECLARATION>
MatrixMap<MATRIX_COLUMN_DYNAMIC_TEMPLATES>& MatrixMap<MATRIX_COLUMN_DYNAMIC_TEMPLATES>::operator=(
	const MatrixMap<MATRIX_COLUMN_DYNAMIC_TEMPLATES>& other)
{
	for (index_t i = 0; i < this->rows() * this->cols(); ++i)
		this->_mappedData[i] = other._mappedData[i];

	return *this;
}

template <MATRIX_COLUMN_TEMPLATES_DECLARATION>
Arithmetic& MatrixMap<MATRIX_COLUMN_TEMPLATES>::operator[](index_t row)
{
	ASSERT(row < this->rows(), "Index out of bounds.");
	return this->_mappedData[row];
}
template <MATRIX_COLUMN_DYNAMIC_TEMPLATES_DECLARATION>
Arithmetic& MatrixMap<MATRIX_COLUMN_DYNAMIC_TEMPLATES>::operator[](index_t row)
{
	ASSERT(row < this->rows(), "Index out of bounds.");
	return this->_mappedData[row];
}

template <MATRIX_COLUMN_TEMPLATES_DECLARATION>
const Arithmetic& MatrixMap<MATRIX_COLUMN_TEMPLATES>::operator[](index_t row) const
{
	ASSERT(row < this->rows(), "Index out of bounds.");
	return this->_mappedData[row];
}
template <MATRIX_COLUMN_DYNAMIC_TEMPLATES_DECLARATION>
const Arithmetic& MatrixMap<MATRIX_COLUMN_DYNAMIC_TEMPLATES>::operator[](index_t row) const
{
	ASSERT(row < this->rows(), "Index out of bounds.");
	return this->_mappedData[row];
}

template <MATRIX_COLUMN_TEMPLATES_DECLARATION>
Arithmetic MatrixMap<MATRIX_COLUMN_TEMPLATES>::length() const
{
	Arithmetic rVal = Arithmetic(0);

	for (index_t row = 0; row < this->rows(); ++row)
		rVal += square(this->_mappedData[row]);

	return std::sqrt(rVal);
}
template <MATRIX_COLUMN_DYNAMIC_TEMPLATES_DECLARATION>
Arithmetic MatrixMap<MATRIX_COLUMN_DYNAMIC_TEMPLATES>::length() const
{
	Arithmetic rVal = Arithmetic(0);

	for (index_t row = 0; row < this->rows(); ++row)
		rVal += square(this->_mappedData[row]);

	return std::sqrt(rVal);
}

template <MATRIX_COLUMN_TEMPLATES_DECLARATION>
Arithmetic MatrixMap<MATRIX_COLUMN_TEMPLATES>::lengthSquared() const
{
	Arithmetic rVal = Arithmetic(0);

	for (index_t row = 0; row < this->rows(); ++row)
		rVal += square(this->_mappedData[row]);

	return rVal;
}
template <MATRIX_COLUMN_DYNAMIC_TEMPLATES_DECLARATION>
Arithmetic MatrixMap<MATRIX_COLUMN_DYNAMIC_TEMPLATES>::lengthSquared() const
{
	Arithmetic rVal = Arithmetic(0);

	for (index_t row = 0; row < this->rows(); ++row)
		rVal += square(this->_mappedData[row]);

	return rVal;
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