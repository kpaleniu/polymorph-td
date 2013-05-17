#include "test_io/DataStorageStreamTest.hpp"

#include <io/DataStorageStream.hpp>
#include <test/test.hpp>

#include <memory>

namespace {

struct DataTestStruct
{
	char aChar;
	int aInt;
	char bChar;
	int bInt;
};

std::unique_ptr<DataTestStruct[]> createData(std::size_t size)
{
	std::unique_ptr<DataTestStruct[]> data(new (std::nothrow) DataTestStruct[size]);

	for (std::size_t i = 0; i < size; ++i)
	{
		data[i].aChar = char(i);
		data[i].aInt = i + 1;
		data[i].bChar = char(i + 2);
		data[i].bInt = i + 3;
	}

	return data;
}

}

void testStructRead()
{
	const std::size_t dataSize = 100;
	
	std::unique_ptr<DataTestStruct[]> data(createData(dataSize));

	if (!data)
		test::cannotRun();


	io::DataStorageInputStream dsis(data.get(), dataSize * sizeof(DataTestStruct));

	for (int i = 0; i < dataSize; ++i)
	{
		DataTestStruct readStruct;
		dsis >> readStruct;

		test::assertEqual(readStruct.aChar, char(i));
		test::assertEqual(readStruct.aInt, i + 1);
		test::assertEqual(readStruct.bChar, char(i + 2));
		test::assertEqual(readStruct.bInt, i + 3);
	}

	ASSERT_EXCEPTION
	(
		io::IOException,
		{
			DataTestStruct readStruct;
			dsis >> readStruct;
		}
	);
}

void testStructPrimitiveRead()
{
	const std::size_t dataSize = 100;
	
	std::unique_ptr<DataTestStruct[]> data(createData(dataSize));

	if (!data)
		test::cannotRun();

	io::DataStorageInputStream dsis(data.get(), dataSize * sizeof(DataTestStruct));

	for (int i = 0; i < dataSize; ++i)
	{
		char tempC;
		int tempI;

		dsis >> tempC >> tempI;
		test::assertEqual(tempC, char(i));
		test::assertEqual(tempI, i + 1);

		dsis >> tempC >> tempI;
		test::assertEqual(tempC, char(i + 2));
		test::assertEqual(tempI, i + 3);
	}

	ASSERT_EXCEPTION
	(
		io::IOException,
		{
			int i;
			dsis >> i;
		}
	);
}