#include <test/test.hpp>

#include <Endianess.hpp>

// #define PM_ASSERT_BUILD_FAILS

#ifdef PM_ASSERT_BUILD_FAILS

	struct TestStruct
	{
		int a, b;

		TestStruct() 
		{}

		TestStruct(int) 
		{}

		TestStruct& operator=(int)
		{ return *this; }
	};

#endif

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

#define ADD_IDENTITY_TEST(type) \
	test::addTest("Identity Test " #type + std::to_string(8 * sizeof(type)), testSameEndianess<type>)

#define ADD_CONVERT_TEST(type) \
	test::addTest("Convert Test " #type + std::to_string(8 * sizeof(type)), testToggleEndianess<type>)

int main(int, char*[])
{
	test::addTest("Endian Unique Test", testUniqueness);

	ADD_IDENTITY_TEST(short);
	ADD_IDENTITY_TEST(int);
	ADD_IDENTITY_TEST(long);
	ADD_IDENTITY_TEST(long long);
	ADD_IDENTITY_TEST(unsigned short);
	ADD_IDENTITY_TEST(unsigned int);
	ADD_IDENTITY_TEST(unsigned long);
	ADD_IDENTITY_TEST(unsigned long long);
	ADD_IDENTITY_TEST(float);
	ADD_IDENTITY_TEST(double);
	ADD_IDENTITY_TEST(long double);

	ADD_CONVERT_TEST(short);
	ADD_CONVERT_TEST(int);
	ADD_CONVERT_TEST(long);
	ADD_CONVERT_TEST(long long);
	ADD_CONVERT_TEST(unsigned short);
	ADD_CONVERT_TEST(unsigned int);
	ADD_CONVERT_TEST(unsigned long);
	ADD_CONVERT_TEST(unsigned long long);
	ADD_CONVERT_TEST(float);
	ADD_CONVERT_TEST(double);
	ADD_CONVERT_TEST(long double);
	
#ifdef PM_ASSERT_BUILD_FAILS
	test::addTest("Identity Test (shouldn't build)", testSameEndianess<TestStruct>);
	test::addTest("Convert Test (shouldn't build)", testToggleEndianess<TestStruct>);
#endif

	return test::runTests();
}
