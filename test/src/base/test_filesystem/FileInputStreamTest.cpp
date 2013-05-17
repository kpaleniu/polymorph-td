#include "test_filesystem/FileInputStreamTest.hpp"

#include <test/test.hpp>
#include <filesystem/FileInputStream.hpp>
#include <filesystem/FileException.hpp>

#include <fstream>

namespace {

bool createTestFile(const char* path, std::size_t size)
{
	std::ios_base::openmode mode = std::ios_base::out | std::ios_base::binary;

	std::ofstream fileOut(path, mode);

	if (!fileOut)
		return false;

	for (std::size_t i = 0; i < size; ++i)
	{
		fileOut << unsigned char(i);

		if (!fileOut)
			return false;
	}

	return true;
}

}


void testRead()
{
	std::size_t dataSize = 256;
	test::assume(createTestFile("TestFile.txt", dataSize));

	filesystem::FileInputStream fis("TestFile.txt");

	for (std::size_t i = 0; i < dataSize; ++i)
	{
		unsigned char tempC;

		test::assertEqual(fis.available(), dataSize - i);

		fis >> tempC;

		test::assertEqual(tempC, unsigned char(i));
	}

	test::assertEqual(fis.available(), std::size_t(0));

	ASSERT_EXCEPTION
	(
		filesystem::FileReadException,
		{
			unsigned char tempC;
			fis >> tempC;
		}
	);
}
