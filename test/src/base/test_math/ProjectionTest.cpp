#include "test_math/ProjectionTest.hpp"

#include <test/test.hpp>
#include <math/Projection.hpp>

namespace {

void testProject()
{
	using namespace math;

	{
		// Identity ortho projection.
		float
			left = -1.0f,
			right = 1.0f,
			bottom = -1.0f,
			top = 1.0f,
			near = 1.0f,
			far = -1.0f;

		auto proj = Projection<float, true>::ortho(left, right, bottom, top, near, far);

		Matrix<float, 3, 1, true> vec;
		vec(0, 0) = 0.5f;
		vec(1, 0) = 0.25f;
		vec(2, 0) = -0.75f;

		Matrix<float, 3, 1, true> vecRes = proj * vec;

		test::assertEqual(vec, vecRes);

		proj.inverse();

		vecRes = proj * vec;

		test::assertEqual(vec, vecRes);
	}


}

}


void addProjectionTests()
{
	test::addTest("Projection Test", testProject);
}