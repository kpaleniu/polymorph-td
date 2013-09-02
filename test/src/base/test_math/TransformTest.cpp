#include "test_math/TransformTest.hpp"

#include <test/test.hpp>
#include <math/Transform.hpp>
#include <math/Transform2.hpp>
#include <math/Quaternion.hpp>

namespace {

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

	{
		Transform2<int> trans;

		Matrix<int, 2, 1> v2 = { 1, 2 };

		test::assertEqual(v2, trans * v2, "Transform2 ctor not identity.");
	}

	{
		auto trans = Transform2<real_t>::createRotation(HALF_PI);

		Matrix<real_t, 2, 1> v2 = { 1, 0 };
		Matrix<real_t, 2, 1> exp = { 0, 1 };

		auto res = trans * v2;

		test::assertAlmostEqual(res[0], exp[0], eps);
		test::assertAlmostEqual(res[1], exp[1], eps);
	}

	{
		auto trans = Transform2<real_t>::createScaling(2);
		Matrix<real_t, 2, 1> v2 = { 1, 0.5 };
		Matrix<real_t, 2, 1> exp = { 2, 1 };

		auto res = trans * v2;

		test::assertAlmostEqual(res[0], exp[0], eps);
		test::assertAlmostEqual(res[1], exp[1], eps);
	}

	{
		auto trans = Transform2<real_t>::createScaling(Matrix<real_t, 2, 1>{ 2, 1 });
		Matrix<real_t, 2, 1> v2 = { 1, 0.5 };
		Matrix<real_t, 2, 1> exp = { 2, 0.5 };

		auto res = trans * v2;

		test::assertAlmostEqual(res[0], exp[0], eps);
		test::assertAlmostEqual(res[1], exp[1], eps);
	}

	{
		auto trans = Transform2<real_t>::createTranslation(Matrix<real_t, 2, 1>{ 2, 1 });
		Matrix<real_t, 2, 1> v2 = { 1, 0.5 };
		Matrix<real_t, 2, 1> exp = { 3, 1.5 };

		auto res = trans * v2;

		test::assertAlmostEqual(res[0], exp[0], eps);
		test::assertAlmostEqual(res[1], exp[1], eps);
	}

	{
		Transform2<real_t> trans1;

		trans1.scale()       = Matrix<real_t, 2, 1>{0.1f, -0.5f};
		trans1.translation() = Matrix<real_t, 2, 1>{1.5f, 8.5f};
		trans1.rotation()    = 4.15f;

		auto trans2 = 
			Transform2<real_t>::createFromAffine(trans1.asAffineMatrix2());

		auto mat1 = trans1.asAffineMatrix2();
		auto mat2 = trans2.asAffineMatrix2();

		int i = 0;
	}

	{
		Transform2<real_t> trans1;
		Transform2<real_t> trans2;

		trans1.rotation() = PI * 0.12f;
		trans2.rotation() = PI * 1.32f;

		trans1.scale() = Matrix<real_t, 2, 1>({ 1.5f, -3.8f });
		trans2.scale() = Matrix<real_t, 2, 1>({ 0.1f, 1.8f });

		trans1.translation() = Matrix<real_t, 2, 1>({ 1.0f, 0.8f });
		trans2.scale() = Matrix<real_t, 2, 1>({ 3.1f, 5.7f });

		auto trans3 = trans1 * trans2;
		Matrix<real_t, 3, 3> mat = trans1.asAffineMatrix2() * trans2.asAffineMatrix2();
		Matrix<real_t, 3, 3> mat2 = trans3.asAffineMatrix2();

		Matrix<real_t, 2, 1> v2 = { 1.0f, 0.5f };

		Matrix<real_t, 2, 1> vA = trans3 * v2;
		Matrix<real_t, 3, 1> vB = mat * Matrix<real_t, 3, 1>{v2[0], v2[1], 1.0f};
		Matrix<real_t, 2, 1> vC = trans2 * (trans1 * v2);

		test::assertEqual(vA[0], vB[0]);
		test::assertEqual(vA[1], vB[1]);

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