#include "test_math/TransformTest.hpp"

#include <test/test.hpp>
#include <math/Transform.hpp>

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
		auto trans = Transform<int, true>::translate(1, 2, 3);

		Matrix<int, 3, 1, true> vec2;

		vec2(0, 0) = 2;
		vec2(1, 0) = 4;
		vec2(2, 0) = 6;

		auto vecRes = trans * vec;

		test::assertEqual(vec2, vecRes);
	}

	{
		auto trans = Transform<int, true>::scale(1, 2, 3);

		Matrix<int, 3, 1, true> vec2;

		vec2(0, 0) = 1;
		vec2(1, 0) = 4;
		vec2(2, 0) = 9;

		auto vecRes = trans * vec;

		test::assertEqual(vec2, vecRes);
	}
}


}


void addTransformTests()
{
	test::addTest("Transform Constructors Test", testConstructors);
}