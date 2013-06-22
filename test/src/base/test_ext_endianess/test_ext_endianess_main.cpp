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

	PunUnion flippedData;
	flippedData.scalar = flipEndianess(data.scalar);

	for (int i = 0; i < sizeof(Scalar); ++i)
		test::assertEqual(data.c[i], flippedData.c[sizeof(Scalar) - 1 - i]);
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

#define ADD_CONVERT_TEST(type) \
	test::addTest("Convert Test " #type + std::to_string(8 * sizeof(type)), testToggleEndianess<type>)

int main(int, char*[])
{
	test::addTest("Endian Unique Test", testUniqueness);

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
