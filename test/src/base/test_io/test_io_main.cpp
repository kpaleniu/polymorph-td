#include "test/test.hpp"

#include "test_io/DataStorageStreamTest.hpp"

int main(int /*argc*/, char* /*argv*/[])
{
	test::addTest("Test Struct Read", testStructRead);
	test::addTest("Test Primitive Read", testStructPrimitiveRead);

	return test::runTests();
}