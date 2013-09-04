#include "test_math/MatrixTest.hpp"

#include <test/test.hpp>
#include <math/Matrix.hpp>

namespace {

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
void testConstructors()
{
	using namespace math;

	{
		Matrix<Arithmetic, Rows, Cols, RowMajor> mat;

		for (index_t row = 0; row < Rows; ++row)
			for (index_t col = 0; col < Cols; ++col)
				test::assertEqual(mat(row, col), Arithmetic(0));
	}

}

template <typename Arithmetic, unsigned int Dim, bool RowMajor>
void testSquareConstructors()
{
	using namespace math;

	{
		Arithmetic diagonal = 2;
		Matrix<Arithmetic, Dim, Dim, RowMajor> mat((Arithmetic(diagonal)));

		for (index_t row = 0; row < Dim; ++row)
		{
			for (index_t col = 0; col < Dim; ++col)
			{
				if (col == row)
					test::assertEqual(mat(row, col), diagonal);
				else
					test::assertEqual(mat(row, col), Arithmetic(0));
			}
		}
	}
}

void testVectorConstructors()
{
	using namespace math;

	{
		Matrix<int, 4, 1, true> vec4 = {0, 1, 2, 3};

		test::assertEqual(vec4[0], 0);
		test::assertEqual(vec4[1], 1);
		test::assertEqual(vec4[2], 2);
		test::assertEqual(vec4[3], 3);
	}
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
void testArithmetics()
{
	using namespace math;

	{
		Matrix<Arithmetic, Rows, Cols, RowMajor> mat;

		for (index_t row = 0; row < Rows; ++row)
			for (index_t col = 0; col < Cols; ++col)
				mat(row, col) = row + Arithmetic(2) * col;

		Matrix<Arithmetic, Rows, Cols, RowMajor> mat2 = mat * Arithmetic(2);
		for (index_t row = 0; row < Rows; ++row)
			for (index_t col = 0; col < Cols; ++col)
				test::assertEqual(mat2(row, col), Arithmetic((row + Arithmetic(2) * col) * Arithmetic(2)));
	}

	{
		Matrix<Arithmetic, Rows, Cols, RowMajor> mat;

		for (index_t row = 0; row < Rows; ++row)
			for (index_t col = 0; col < Cols; ++col)
				mat(row, col) = row + Arithmetic(2) * col;

		Matrix<Arithmetic, Rows, Cols, RowMajor> mat2 = mat / Arithmetic(2);
		for (index_t row = 0; row < Rows; ++row)
			for (index_t col = 0; col < Cols; ++col)
				test::assertEqual(mat2(row, col), Arithmetic((row + Arithmetic(2) * col) / Arithmetic(2) ));
	}

	{
		Matrix<Arithmetic, Rows, Cols, RowMajor> mat1, mat2;

		for (index_t row = 0; row < Rows; ++row)
		{
			for (index_t col = 0; col < Cols; ++col)
			{
				mat1(row, col) = row + Arithmetic(2) * col;
				mat2(row, col) = col + Arithmetic(2) * row;
			}
		}

		Matrix<Arithmetic, Rows, Cols, RowMajor> mat3 = mat1 + mat2;

		for (index_t row = 0; row < Rows; ++row)
			for (index_t col = 0; col < Cols; ++col)
				test::assertEqual(mat3(row, col), 
								  Arithmetic(Arithmetic(3) * row + Arithmetic(3) * col));
	}
}

void testMatrixMult()
{
	using namespace math;

	int m1[] = 
	{
		-3,  6,  0,  5,
		-2, -1,  2,  7,
		-4,  1,  3,  8,
		 4,  9, 10, 11
	};

	int m2[] =
	{
		12,  6,
		13, 14,
		15, 16,
		 4, -2
	};

	int m3[] =
	{
		 62,  56,
		 21,  -8,
		 42,  22,
		359, 288
	};

	int m4[] =
	{
		 3,  6,  0,  5,
		-2, -1,  5,  7,
		-4,  7,  3, -3,
		 4,  9, 10,  1
	};

	{
		Matrix<int, 4, 4, true> mat1(m1);
		Matrix<int, 4, 2, true> mat2(m2);

		Matrix<int, 4, 2, true> mat3(m3);
		
		Matrix<int, 4, 2, true> resMat = mat1 * mat2;

		test::assertEqual(mat3, resMat);
	}

	{
		Matrix<int, 4, 4, true> mat1(m1);
		Matrix<int, 4, 4, true> mat2(m4);

		Matrix<int, 4, 4, true> mat3 = mat1 * mat2;
		mat1 *= mat2;

		test::assertEqual(mat3, mat1);
	}
}

void testInverse()
{
	using namespace math;

	int m1[] =
	{
		1, 2, 3,
		0, 1, 4,
		5, 6, 0
	};

	int m2[] =
	{
		-24,  18,  5,
		 20, -15, -4,
		 -5,   4,  1
	};

	Matrix<int, 3, 3, true> mat1(m1);
	Matrix<int, 3, 3, true> mat2(m2);
	Matrix<int, 3, 3, true> mat3 = inverse(mat1);

	test::assertEqual(mat2, mat3);
	test::assertEqual(mat1 * mat2, Matrix<int, 3, 3, true>::IDENTITY);
}

void testStaticData()
{
	auto matZero33 = math::Matrix<int, 3, 3>::ZERO;
	auto matIdentity33 = math::Matrix<int, 3, 3>::IDENTITY;

	auto matZero43 = math::Matrix<int, 4, 3>::ZERO;
	auto matZero41 = math::Matrix<int, 4, 1>::ZERO;

	// math::Matrix<int, 4, 3>::IDENTITY; // build error
	// math::Matrix<int, 4, 1>::IDENTITY; // build error

	test::assertEqual(matZero33, math::Matrix<int, 3, 3>());
	test::assertEqual(matIdentity33, math::Matrix<int, 3, 3>(1));
	test::assertEqual(matZero43, math::Matrix<int, 4, 3>());
	test::assertEqual(matZero41, math::Matrix<int, 4, 1>());
}

}

#define ADD_CONSTRUCTOR_TEST(type, rows, cols, rowMajor) \
	test::addTest("Constructor test <" #type ", " #rows ", " #cols ", " #rowMajor ">", \
				  testConstructors<type, rows, cols, rowMajor>); \
	if (rows == cols) \
		test::addTest("Square constructor test <" #type ", " #rows ", " #rowMajor ">", \
					  testSquareConstructors<type, rows, rowMajor>)

#define ADD_ARITHMETICS_TEST(type, rows, cols, rowMajor) \
	test::addTest("Arithmetic text <" #type ", " #rows ", " #cols ", " #rowMajor ">", \
				  testArithmetics<type, rows, cols, rowMajor>)

void addMatrixTests()
{
	ADD_CONSTRUCTOR_TEST(float, 2, 2, true);
	ADD_CONSTRUCTOR_TEST(float, 2, 3, true);
	ADD_CONSTRUCTOR_TEST(float, 3, 2, true);

	ADD_CONSTRUCTOR_TEST(float, 2, 2, false);
	ADD_CONSTRUCTOR_TEST(float, 2, 3, false);
	ADD_CONSTRUCTOR_TEST(float, 3, 2, false);

	ADD_CONSTRUCTOR_TEST(int, 2, 2, true);
	ADD_CONSTRUCTOR_TEST(int, 2, 3, true);
	ADD_CONSTRUCTOR_TEST(int, 3, 2, true);

	ADD_CONSTRUCTOR_TEST(int, 2, 2, false);
	ADD_CONSTRUCTOR_TEST(int, 2, 3, false);
	ADD_CONSTRUCTOR_TEST(int, 3, 2, false);

	ADD_ARITHMETICS_TEST(float, 2, 2, true);
	ADD_ARITHMETICS_TEST(float, 2, 3, true);
	ADD_ARITHMETICS_TEST(float, 3, 2, true);

	ADD_ARITHMETICS_TEST(float, 2, 2, false);
	ADD_ARITHMETICS_TEST(float, 2, 3, false);
	ADD_ARITHMETICS_TEST(float, 3, 2, false);

	ADD_ARITHMETICS_TEST(int, 2, 2, true);
	ADD_ARITHMETICS_TEST(int, 2, 3, true);
	ADD_ARITHMETICS_TEST(int, 3, 2, true);

	ADD_ARITHMETICS_TEST(int, 2, 2, false);
	ADD_ARITHMETICS_TEST(int, 2, 3, false);
	ADD_ARITHMETICS_TEST(int, 3, 2, false);

	test::addTest("Matrix Multiplication Test", testMatrixMult);
	test::addTest("Matrix 3x3 Inverse Test", testInverse);
	test::addTest("Vector constructor Test", testVectorConstructors);
}