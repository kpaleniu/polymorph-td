#ifndef TEST_TEST_HPP
#define TEST_TEST_HPP

#include <Exception.hpp>

#include <functional>
#include <string>

namespace test {

PM_MAKE_EXCEPTION_CLASS(Failed, std::exception);
PM_MAKE_EXCEPTION_CLASS(CannotRun, std::exception);


typedef std::function<void ()> Test;

void addTest(const std::string& testName, const Test& test);
int runTests();

/**
 * Called to indicate test failure.
 */
inline void fail();

/**
 * Called to indicate test setup couldn't complete.
 */
inline void cannotRun();

inline void assume(bool expr);

inline void assert(bool expr);

template <typename T>
inline void assertEqual(const T& a, const T& b);

template <typename T>
inline void assertNotEqual(const T& a, const T& b);

}

#define ASSERT_EXCEPTION(exceptionType, block)	\
{												\
	bool detail__caughtException = false;		\
	try											\
	{ block }									\
	catch (exceptionType&)						\
	{ detail__caughtException = true; }			\
	test::assert(detail__caughtException);		\
}

#define ASSUME_NO_EXCEPTION(exceptionType, block) \
{												\
	bool detail__caughtException = false;		\
	try											\
	{ block }									\
	catch (exceptionType&)						\
	{ detail__caughtException = true; }			\
	test::assume(!detail__caughtException);		\
}

#include "test/test.inl"

#endif