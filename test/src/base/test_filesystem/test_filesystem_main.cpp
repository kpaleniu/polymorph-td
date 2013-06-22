#include "test/test.hpp"

#include "test_filesystem/FileInputStreamTest.hpp"
#include "test_filesystem/FileOutputStreamTest.hpp"

int main(int /*argc*/, char* /*argv*/[])
{
	test::addTest("Test Read", testRead);
	test::addTest("Test Write", testWrite);

	return test::runTests();
}