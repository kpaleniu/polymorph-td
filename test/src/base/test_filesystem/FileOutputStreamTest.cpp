#include "test_filesystem/FileOutputStreamTest.hpp"

#include <filesystem/FileOutputStream.hpp>

#include <test/test.hpp>

#include <fstream>
#include <memory>

namespace {

void createTestFile(const char* path, std::size_t size)
{
	filesystem::FileOutputStream fos(path);

	for (std::size_t i = 0; i < size; ++i)
		fos << (char) i;
}

}



void testWrite()
{
	createTestFile("TestWrite.txt", 20);

	std::ifstream ifs("TestWrite.txt", std::ios_base::binary | std::ios_base::in);

	test::assume(ifs, "Cannot open file.");

	for (int i = 0; i < 20; ++i)
	{
		char temp;
		ifs.get(temp);

		test::assertTrue( ifs );

		test::assertEqual(temp, (char) i, "Unexpected file content.");
		
	}

	test::assertTrue( ifs );

	char c;
	ifs.get(c);

	test::assertTrue( !ifs );
}