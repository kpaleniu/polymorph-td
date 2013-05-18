#include <test/test.hpp>

#include <Endianess.hpp>

template <typename Scalar>
void testToggleEndianess()
{
	union PunUnion
	{
		Scalar scalar;
		unsigned char c[sizeof(Scalar)];
	} data;

	data.scalar = Scalar(1);

	if (isBigEndian())
	{
		test::assume( !isLittleEndian() );

		auto littleEndianData = copyAsLittleEndian(data.scalar);

		for (int i = 0; i < sizeof(Scalar); ++i)
			test::assertEqual(data.c[i], littleEndianData[sizeof(Scalar) - 1 - i]);
	}
	else
	{
		test::assume( isLittleEndian() );
		
		auto bigEndianData = copyAsBigEndian(data.scalar);

		for (int i = 0; i < sizeof(Scalar); ++i)
			test::assertEqual(data.c[i], bigEndianData[sizeof(Scalar) - 1 - i]);
	}
}

template <typename Scalar>
void testSameEndianess()
{
	union PunUnion
	{
		Scalar scalar;
		unsigned char c[sizeof(Scalar)];
	} data;

	data.scalar = Scalar(1);

	if (isBigEndian())
	{
		test::assume( !isLittleEndian() );

		auto bigEndianData = copyAsBigEndian(data.scalar);

		for (int i = 0; i < sizeof(Scalar); ++i)
			test::assertEqual(data.c[i], bigEndianData[i]);
	}
	else
	{
		test::assume( isLittleEndian() );
		
		auto littleEndianData = copyAsLittleEndian(data.scalar);

		for (int i = 0; i < sizeof(Scalar); ++i)
			test::assertEqual(data.c[i], littleEndianData[i]);
	}
}

void testUniqueness()
{
	test::assert
	( 
		( isBigEndian() && !isLittleEndian() ) 
		|| 
		( isLittleEndian() && !isBigEndian() ) 
	);
}

int main(int, char*[])
{
	test::addTest("Endian Unique Test", testUniqueness);

	test::addTest("Identity Test (short)", testSameEndianess<short>);
	test::addTest("Identity Test (int)", testSameEndianess<int>);
	test::addTest("Identity Test (long)", testSameEndianess<long>);
	test::addTest("Identity Test (long long)", testSameEndianess<long long>);

	test::addTest("Convert Test (short)", testToggleEndianess<short>);			// Fails
	test::addTest("Convert Test (int)", testToggleEndianess<int>);				// Fails
	test::addTest("Convert Test (long)", testToggleEndianess<long>);
	test::addTest("Convert Test (long long)", testToggleEndianess<long long>);	// Fails

	test::addTest("Identity Test (float)", testSameEndianess<float>);
	test::addTest("Convert Test (float)", testToggleEndianess<float>);

	
#ifdef PM_ASSERT_BUILD_FAILS
	struct TestStruct
	{
		int a, b;
	};

	test::addTest("Identity Test (shouldn't build)", testSameEndianess<TestStruct>);
	test::addTest("Convert Test (shouldn't build)", testToggleEndianess<TestStruct>);
#endif

	return test::runTests();
}
