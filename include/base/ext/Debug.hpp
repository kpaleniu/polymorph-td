/**
 * @file Debug.hpp
 *
 */

#ifndef DEBUG_HPP_
#define DEBUG_HPP_

#include "Format.hpp"
#include <string>



namespace debug {

// Explicit underlying type for Severity enumeration.
typedef size_t severity_t;

// Severity level enumeration. Used to control output verbosity levels.
enum class Severity : severity_t {
	Fatal,
	Error,
	Info,
	Debug,
	Verbose
};

namespace detail {

// Should always be equal to the last value in Severity enumeration.
const Severity lowestSeverity = Severity::Verbose;

// If verbosity level is not explicitly defined, default to lowest.
#ifndef POLYMORPH_VERBOSITY
#define POLYMORPH_VERBOSITY lowestSeverity
#endif

// Helper template class for filtering output by severity.
template <Severity OutputLevel>
struct is_severity_enabled
{
	static const severity_t _level     = static_cast<severity_t>(OutputLevel);
	static const severity_t _verbosity = static_cast<severity_t>(POLYMORPH_VERBOSITY);
	static const bool value = (_level <= _verbosity);
};

// Actual underlying printing implementation.
void print_impl(Severity level, const char* file, long line, const char* tag, const std::string& message);

// Base template definition for enabled severity levels.
template <Severity OutputLevel, bool Enabled = is_severity_enabled<OutputLevel>::value>
struct print
{
#if defined(_MSC_VER)

// use Microsoft's own hacks to implement variadic template emulation
#define OUTPUT_IMPL(TEMPLATE_LIST, PADDING_LIST, LIST, COMMA, X1, X2, X3, X4) \
	TEMPLATE_LIST(_CLASS_TYPE) \
	static void output(const char* file, long line, const char* tag, \
		const char* message COMMA \
		LIST(_TYPE_REFREF_ARG)) \
	{ \
		print_impl(OutputLevel, file, line, tag, \
			format(message COMMA LIST(_FORWARD_ARG))); \
	}
	
	_VARIADIC_EXPAND_0X(OUTPUT_IMPL, , , , )
#undef OUTPUT_IMPL

#else

	// all other reasonably up-to-date compilers should support variadic templates
	template <typename ... Args>
	static void output(const char* file, long line, const char* tag,
		const char* message, Args&& ... args)
	{
		print_impl(OutputLevel, file, line, tag,
			format(message, std::forward<Args>(args)...));
	}

#endif
};

// Explicit partial template specialization for disabled severity levels.
template <Severity OutputLevel>
struct print<OutputLevel, false>
{
	static void output(...) {}
};

}	// namespace detail
}	// namespace debug


// helper macro for including filename and line number in convenience macros
#define PRINT_WRAPPER(level, tag, ...) debug::detail::print<level>::output(\
	__FILE__, __LINE__, tag, __VA_ARGS__)

// convenience macros for different severity levels
#define FATAL_OUT(tag, ...)   PRINT_WRAPPER(debug::Severity::Fatal,   tag, __VA_ARGS__)
#define ERROR_OUT(tag, ...)   PRINT_WRAPPER(debug::Severity::Error,   tag, __VA_ARGS__)
#define INFO_OUT(tag, ...)    PRINT_WRAPPER(debug::Severity::Info,    tag, __VA_ARGS__)
#define DEBUG_OUT(tag, ...)   PRINT_WRAPPER(debug::Severity::Debug,   tag, __VA_ARGS__)
#define VERBOSE_OUT(tag, ...) PRINT_WRAPPER(debug::Severity::Verbose, tag, __VA_ARGS__)


#endif /* DEBUG_HPP_ */
