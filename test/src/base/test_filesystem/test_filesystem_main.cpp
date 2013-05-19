#include "test/test.hpp"

#include "test_filesystem/FileInputStreamTest.hpp"

int main(int /*argc*/, char* /*argv*/[])
{
	test::addTest("Test Read Text", testRead);

	return test::runTests();
}