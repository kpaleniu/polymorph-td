#include "test_math/TransformTest.hpp"

#include <test/test.hpp>
#include <math/Transform.hpp>
#include <math/Transform2.hpp>
#include <math/Quaternion.hpp>

#include <math/Matrix.hpp>

#include <Assert.hpp>

namespace {

template <typename Arithmetic, unsigned int Rows, unsigned int Cols, bool RowMajor>
void assertAlmostEqualMatrices(
	const math::MatrixMap<Arithmetic, Rows, Cols, RowMajor>& m1,
	const math::MatrixMap<Arithmetic, Rows, Cols, RowMajor>& m2,
	Arithmetic eps)
{
	ASSERT(m1.rows() == m2.rows() && m1.cols() == m2.cols(), "Bad dimensions");

	unsigned int rows = m1.rows();
	unsigned int cols = m1.cols();

	for (unsigned int row = 0; row < rows; ++row)
		for (unsigned int col = 0; col < cols; ++col)
			test::assertAlmostEqual(m1(row, col), m2(row, col), eps);
}

void testConstructors()
{
	using namespace math;

	Matrix<int, 3, 1, true> vec;

	vec(0, 0) = 1;
	vec(1, 0) = 2;
	vec(2, 0) = 3;

	{
		Transform<int, true> trans;

		Matrix<int, 3, 1, true> vec2 = trans * vec;

		test::assertEqual(vec2, vec);
	}

	{
		auto trans = Transform<int, true>::createTranslation(1, 2, 3);

		Matrix<int, 3, 1, true> vec2;

		vec2(0, 0) = 2;
		vec2(1, 0) = 4;
		vec2(2, 0) = 6;

		auto vecRes = trans * vec;

		test::assertEqual(vec2, vecRes);
	}

	{
		auto trans = Transform<int, true>::createScaling(1, 2, 3);

		Matrix<int, 3, 1, true> vec2;

		vec2(0, 0) = 1;
		vec2(1, 0) = 4;
		vec2(2, 0) = 9;

		auto vecRes = trans * vec;

		test::assertEqual(vec2, vecRes);
	}

	{
		auto quat = 
			Transform<real_t, true>::createRotation
			(
				Quaternion<real_t, true>::angleAxis
				(
					PI, 
					Matrix<real_t, 3, 1, true>{0.0f, 0.0f, 1.0f}
				)
			);

		Matrix<float, 4, 1, true> vec4;
		Matrix<float, 3, 1, true> vec3;

		vec4[0] = 1.0f;
		vec4[1] = 2.0f;
		vec4[3] = 1.0f;

		vec3[0] = 1.0f;
		vec3[1] = 2.0f;

		auto resVec1 = quat.asAffineMatrix() * vec4;
		auto resVec2 = quat * vec3;

		test::assertEqual(resVec1[0], resVec2[0]);
		test::assertEqual(resVec1[1], resVec2[1]);
		test::assertEqual(resVec1[2], resVec2[2]);
	}
}

void testTransform2()
{
	using namespace math;

	real_t eps = 0.0001f;

	// Empty constructor
	{ 
		Transform2<int> trans;

		Matrix<int, 2, 1> v2 = { 1, 2 };

		test::assertEqual(v2, trans * v2, "Transform2 ctor not identity.");
	}

	// Rotation factory
	{
		auto trans = Transform2<real_t>::createRotation(HALF_PI);

		Matrix<real_t, 2, 1> v2 = { 1, 0 };
		Matrix<real_t, 2, 1> exp = { 0, 1 };

		auto res = trans * v2;

		assertAlmostEqualMatrices(res, exp, eps);
	}

	// Scale factory
	{
		auto trans = Transform2<real_t>::createScaling(2);
		Matrix<real_t, 2, 1> v2 = { 1, 0.5 };
		Matrix<real_t, 2, 1> exp = { 2, 1 };

		auto res = trans * v2;

		assertAlmostEqualMatrices(res, exp, eps);
	}

	// Translation factory
	{
		auto trans = Transform2<real_t>::createTranslation(Matrix<real_t, 2, 1>{ 2, 1 });
		Matrix<real_t, 2, 1> v2 = { 1, 0.5 };
		Matrix<real_t, 2, 1> exp = { 3, 1.5 };

		auto res = trans * v2;

		assertAlmostEqualMatrices(res, exp, eps);
	}

	// Transform2::operator*(const Vector&)
	{
		Transform2<real_t> trans;

		trans.scale() = 0.1f;
		trans.translation() = Matrix<real_t, 2, 1>{1.5f, 8.5f};
		trans.rotation() = 4.15f;

		Matrix<real_t, 2, 1> v = { 1.5f, -5.2f };

		auto v1 = trans * v;
		auto v2 = trans.asAffineMatrix2() * Matrix<real_t, 3, 1>{v[0], v[1], 1.0f};

		test::assertAlmostEqual(v1[0], v2[0], eps);
		test::assertAlmostEqual(v1[1], v2[1], eps);
	}

	// Transform2::operator*(const Transform2&)
	{
		Transform2<real_t, true> trans1;
		Transform2<real_t, true> trans2;

		trans1.rotation() = PI * 0.12f;
		trans2.rotation() = PI * 1.32f;

		trans1.scale() = 1.5f;
		trans2.scale() = -0.8f;

		trans1.translation() = Matrix<real_t, 2, 1, true>({ 1.0f, 0.8f });
		trans2.translation() = Matrix<real_t, 2, 1, true>({ 3.1f, 5.7f });

		auto trans3 = trans1 * trans2;

		auto mat1 = trans1.asAffineMatrix2() * trans2.asAffineMatrix2();
		auto mat2 = trans3.asAffineMatrix2();

		assertAlmostEqualMatrices(mat1, mat2, eps);
	}

	// Transform2::inverse
	{
		Transform2<real_t, true> trans1;

		trans1.rotation() = PI * 0.12f;
		trans1.scale() = 1.5f;
		trans1.translation() = Matrix<real_t, 2, 1, true>({ 1.0f, 0.8f });

		auto trans2 = trans1.inverse();

		auto res1 = trans1 * trans2;
		auto res2 = trans2 * trans1;

		auto mat1 = res1.asAffineMatrix2();
		auto mat2 = res2.asAffineMatrix2();

		assertAlmostEqualMatrices(mat1,
								  Matrix<real_t, 3, 3, true>::IDENTITY,
								  eps);

		assertAlmostEqualMatrices(mat2,
								  Matrix<real_t, 3, 3, true>::IDENTITY,
								  eps);
	}
}

void testQuaternion()
{
	{
		// TODO
	}
}



}


void addTransformTests()
{
	test::addTest("Transform Constructors Test", testConstructors);
	test::addTest("Transform2 Test", testTransform2);
}