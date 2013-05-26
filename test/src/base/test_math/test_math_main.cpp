#include "test_math/MatrixTest.hpp"
#include "test_math/TransformTest.hpp"
#include "test_math/ProjectionTest.hpp"

#include <test/test.hpp>


int main(int /*argc*/, char* /*argv*/[])
{
	addMatrixTests();
	addTransformTests();
	addProjectionTests();

	return test::runTests();
}