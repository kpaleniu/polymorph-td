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

		for (Matrix<Arithmetic, Rows, Cols, RowMajor>::index_t row = 0; row < Rows; ++row)
		{
			for (Matrix<Arithmetic, Rows, Cols, RowMajor>::index_t col = 0; col < Cols; ++col)
			{
				test::assertEqual(mat(row, col), Arithmetic(0));
			}
		}
	}

	{
		Arithmetic diagonal = 2;
		Matrix<Arithmetic, Rows, Cols, RowMajor> mat((Arithmetic(diagonal)));

		for (Matrix<Arithmetic, Rows, Cols, RowMajor>::index_t row = 0; row < Rows; ++row)
		{
			for (Matrix<Arithmetic, Rows, Cols, RowMajor>::index_t col = 0; col < Cols; ++col)
			{
				if (col == row)
					test::assertEqual(mat(row, col), diagonal);
				else
					test::assertEqual(mat(row, col), Arithmetic(0));
			}
		}
	}
}

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
void testArithmetics()
{
	using namespace math;

	{
		Matrix<Arithmetic, Rows, Cols, RowMajor> mat;

		for (Matrix<Arithmetic, Rows, Cols, RowMajor>::index_t row = 0; row < Rows; ++row)
		{
			for (Matrix<Arithmetic, Rows, Cols, RowMajor>::index_t col = 0; col < Cols; ++col)
			{
				mat(row, col) = row + Arithmetic(2) * col;
			}
		}

		Matrix<Arithmetic, Rows, Cols, RowMajor> mat2 = mat * Arithmetic(2);
		for (Matrix<Arithmetic, Rows, Cols, RowMajor>::index_t row = 0; row < Rows; ++row)
		{
			for (Matrix<Arithmetic, Rows, Cols, RowMajor>::index_t col = 0; col < Cols; ++col)
			{
				test::assertEqual(mat2(row, col), Arithmetic((row + Arithmetic(2) * col) * Arithmetic(2)));
			}
		}
	}

	{
		Matrix<Arithmetic, Rows, Cols, RowMajor> mat;

		for (Matrix<Arithmetic, Rows, Cols, RowMajor>::index_t row = 0; row < Rows; ++row)
		{
			for (Matrix<Arithmetic, Rows, Cols, RowMajor>::index_t col = 0; col < Cols; ++col)
			{
				mat(row, col) = row + Arithmetic(2) * col;
			}
		}

		Matrix<Arithmetic, Rows, Cols, RowMajor> mat2 = mat / Arithmetic(2);
		for (Matrix<Arithmetic, Rows, Cols, RowMajor>::index_t row = 0; row < Rows; ++row)
		{
			for (Matrix<Arithmetic, Rows, Cols, RowMajor>::index_t col = 0; col < Cols; ++col)
			{
				test::assertEqual(mat2(row, col), Arithmetic((row + Arithmetic(2) * col) / Arithmetic(2) ));
			}
		}
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

	{
		Matrix<int, 4, 4, true> mat1(m1);
		Matrix<int, 4, 2, true> mat2(m2);

		Matrix<int, 4, 2, true> mat3(m3);
		
		Matrix<int, 4, 2, true> resMat = mat1 * mat2;

		test::assert(mat3 == resMat);
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

	test::assert(mat2 == mat3);
	test::assert(mat1 * mat2 == Matrix<int, 3, 3, true>::Constants::IDENTITY);
}

void testStaticData()
{
	auto matZero33 = math::Matrix<int, 3, 3>::Constants::ZERO;
	auto matIdentity33 = math::Matrix<int, 3, 3>::Constants::IDENTITY;

	auto matZero43 = math::Matrix<int, 4, 3>::Constants::ZERO;

	// math::Matrix<int, 4, 3>::Constants::IDENTITY; // build error

	test::assert(matZero33 == math::Matrix<int, 3, 3>());
	test::assert(matIdentity33 == math::Matrix<int, 3, 3>(1));
	test::assert(matZero43 == math::Matrix<int, 4, 3>());
}

}

#define ADD_CONSTRUCTOR_TEST(type, rows, cols, rowMajor) \
	test::addTest("Constructor test <" #type ", " #rows ", " #cols ", " #rowMajor ">", \
				  testConstructors<type, rows, cols, rowMajor>)

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
}