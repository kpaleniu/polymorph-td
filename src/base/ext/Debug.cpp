/**
 * @file Debug.cpp
 *
 * Output printing implementations
 */

#include "Assert.hpp"
#include "Debug.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

// MSVS don't catch output from std::cout for windowed applications.
#if defined(_WIN32) && defined(_MSC_VER)
	#include <windows.h>
	#define OS_OUTPUT_IMPL(str) OutputDebugString((str + '\n').c_str())
#else
	#define OS_OUTPUT_IMPL(str) std::cout << str << std::endl
#endif


namespace debug {
namespace detail {
namespace {

// array of severity level identifier tags
const char severity_tag[] = { 'F', 'E', 'I', 'D', 'V' };
const size_t tag_count = sizeof(severity_tag) / sizeof(*severity_tag);
static_assert(tag_count == static_cast<severity_t>(lowestSeverity) + 1,
	"missing severity tags");

// proxy type (for some syntactic sugar) and actual timestamp function
struct time_stamp_proxy {} current_time_stamp;
std::ostream& operator<<(std::ostream& os, time_stamp_proxy)
{
	auto now  = std::chrono::system_clock::now();
	auto time = std::chrono::system_clock::to_time_t(now);

#if defined(_WIN32) && defined(_MSC_VER)

	std::tm _tm;

	{
		auto errNo = localtime_s(&_tm, &time);
		ASSERT(errNo == 0, "Error getting local time.");
	}

	auto tm = &_tm;

#else

	auto tm = std::localtime(&time);

#endif

	// construct a ISO-8601 date+timestamp
	const size_t stamp_length = 4+1+2+1+2 +1+ 2+1+2+1+2;
	char stamp[stamp_length + 1] = {};
	VERIFY(std::strftime(stamp, stamp_length + 1, "%Y-%m-%dT%H:%M:%S", tm) == stamp_length);

	os << stamp;

	// append microseconds
	auto micros = (std::chrono::time_point_cast<std::chrono::microseconds>(now) -
		std::chrono::time_point_cast<std::chrono::seconds>(now)).count();
	os << "." << std::setw(6) << std::setfill('0') << micros;

	return os;
}

// helper function for automatically indenting multi-line messages
template <typename Buf>
void append_message(Buf& buf, const std::string& message, std::streamoff indent_count)
{
	std::string indentation(static_cast<size_t>(indent_count), ' ');
	for (char c : message)
	{
		buf << c; 
		if (c == '\n')
			buf << indentation; 
	}
}

}	// anonymous namespace


void print_impl(
	Severity level,
	const char* /*file*/,
	long /*line*/,
	const char* tag,
	const std::string& message)
{
	char sev_tag = severity_tag[static_cast<severity_t>(level)];

	std::ostringstream buf;
	buf << current_time_stamp << ": ";
	//buf << file << "@" << line << ": ";
	buf << sev_tag << "/" << tag << ' ';

	append_message(buf, message, buf.tellp());

	OS_OUTPUT_IMPL(buf.str());
}

}	// namespace detail
}	// namespace debug

#undef OUTPUT_IMPL
