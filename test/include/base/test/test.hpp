#ifndef TEST_TEST_HPP
#define TEST_TEST_HPP

#include <Exception.hpp>

#include <functional>
#include <string>

namespace test {


PM_MAKE_EXCEPTION_CLASS(TestException, std::exception);

class Failed : public TestException
{
public:
	Failed(const std::string& userMessage) throw()	: _userMessage(userMessage) {}
	const char* what() throw() { return _userMessage.c_str(); }
private:
	std::string _userMessage;
};

class CannotRun : public TestException
{
public:
	CannotRun(const std::string& userMessage) throw()	: _userMessage(userMessage) {}
	const char* what() throw() { return _userMessage.c_str(); }
private:
	std::string _userMessage;
};



typedef std::function<void ()> Test;

void addTest(const std::string& testName, const Test& test);
int runTests();

/**
 * Called to indicate test failure.
 */
inline void fail(const std::string& msg = std::string());

/**
 * Called to indicate test setup couldn't complete.
 */
inline void cannotRun(const std::string& msg = std::string());

inline void assume(bool expr, const std::string& msg = std::string());

inline void assertTrue(bool expr, const std::string& msg = std::string());

template <typename T>
inline void assertEqual(const T& a, const T& b, const std::string& msg = std::string());

template <typename T>
inline void assertNotEqual(const T& a, const T& b, const std::string& msg = std::string());

}

#define ASSERT_EXCEPTION(exceptionType, block)	\
{												\
	bool detail__caughtException = false;		\
	try											\
	{ block }									\
	catch (exceptionType&)						\
	{ detail__caughtException = true; }			\
	test::assertTrue(detail__caughtException);		\
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