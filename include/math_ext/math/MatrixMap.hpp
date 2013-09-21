#ifndef MATRIX_MAP_HPP
#define MATRIX_MAP_HPP

#include "math/types.hpp"

namespace math {

namespace detail {

template <unsigned int Rows, unsigned int Cols>
class DimBasePart
{
public:
	unsigned int rows() const 
	{
		return Rows;
	}
	unsigned int cols() const 
	{
		return Cols;
	}
};

template <>
struct DimBasePart<DYNAMIC, 1u>
{
public:
	unsigned int rows() const 
	{
		return _rows;
	}
	unsigned int cols() const 
	{
		return 1;
	}

protected:
	unsigned int _rows;
};

template <>
struct DimBasePart<1u, DYNAMIC>
{
	//static_assert(false, "1-DYNAMIC matrices not implemented.");
};

template <>
struct DimBasePart<DYNAMIC, DYNAMIC>
{
	//static_assert(false, "DYNAMIC-DYNAMIC matrices not implemented.");
};



template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
class BaseMatrixMap : public DimBasePart<Rows, Cols>
{
public:
	Arithmetic* data();
	const Arithmetic* data() const;

	Arithmetic& operator()(index_t row, index_t col);
	const Arithmetic& operator()(index_t row, index_t col) const;

protected:
	BaseMatrixMap(Arithmetic* data);

	Arithmetic* _mappedData;

private:
	BaseMatrixMap(const BaseMatrixMap<Arithmetic, Rows, Cols, RowMajor>&);
};

}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor = false>
class MatrixMap : public detail::BaseMatrixMap<Arithmetic, Rows, Cols, RowMajor>
{
public:
	MatrixMap(Arithmetic* data = nullptr);

	MatrixMap<Arithmetic, Rows, Cols, RowMajor> &
		operator=(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>& other);

private:
	MatrixMap(const MatrixMap<Arithmetic, Rows, Cols, RowMajor>&);
};

template <typename Arithmetic, unsigned int Rows, bool RowMajor>
class MatrixMap<Arithmetic, Rows, 1u, RowMajor>	:
	public detail::BaseMatrixMap<Arithmetic, Rows, 1u, RowMajor>
{
public:
	MatrixMap(Arithmetic* data = nullptr);

	MatrixMap<Arithmetic, Rows, 1u, RowMajor> &
		operator=(const MatrixMap<Arithmetic, Rows, 1u, RowMajor>& other);

	Arithmetic& operator[](index_t row);
	const Arithmetic& operator[](index_t row) const;

	Arithmetic length() const;
	Arithmetic lengthSquared() const;

private:
	MatrixMap(const MatrixMap<Arithmetic, Rows, 1u, RowMajor>&);
};

template <typename Arithmetic, bool RowMajor>
class MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor> :
	public detail::BaseMatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>
{
public:
	MatrixMap(Arithmetic* data, unsigned int rows);

	MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor> &
		operator=(const MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>& other);

	Arithmetic& operator[](index_t row);
	const Arithmetic& operator[](index_t row) const;

	Arithmetic length() const;
	Arithmetic lengthSquared() const;

private:
	MatrixMap(const MatrixMap<Arithmetic, DYNAMIC, 1u, RowMajor>&);
};


}



#endif