/**
 * @file Format.hpp
 *
 */

#ifndef BOOST_FORMAT_HPP_
#define BOOST_FORMAT_HPP_

#include <string>
#include <boost/format.hpp>



namespace detail {

// end-case override for recursive template functions below
inline std::string basic_format(boost::format& fmt)
{
	return fmt.str();
}

#if defined(_MSC_VER)

// use Microsoft's own hacks to implement variadic template emulation
#define BASIC_FORMAT_IMPL(TEMPLATE_LIST, PADDING_LIST, LIST, COMMA, X1, X2, X3, X4) \
template <typename Arg COMMA LIST(_CLASS_TYPE) > \
inline std::string basic_format(boost::format& fmt, Arg&& arg COMMA LIST(_TYPE_REFREF_ARG)) \
{ \
	return basic_format(fmt % std::forward<Arg>(arg) COMMA LIST(_FORWARD_ARG)); \
}

_VARIADIC_EXPAND_0X(BASIC_FORMAT_IMPL, , , , )
#undef BASIC_FORMAT_IMPL

#else

// all other reasonably up-to-date compilers should support variadic templates
template <typename Arg, typename ... Args>
inline std::string basic_format(boost::format& fmt, Arg&& arg, Args&& ... args)
{
	return basic_format(fmt % std::forward<Arg>(arg), std::forward<Args>(args)...);
}

#endif
}	// namespace detail



// NOTE: special case override; don't perform
// format string parsing if no arguments are given
inline std::string format(const std::string& fmtstr)
{
	return fmtstr;
}

#if defined(_MSC_VER)

// use Microsoft's own hacks to implement variadic template emulation
#define FORMAT_IMPL(TEMPLATE_LIST, PADDING_LIST, LIST, COMMA, X1, X2, X3, X4) \
TEMPLATE_LIST(_CLASS_TYPE) \
inline std::string format(const std::string& fmtstr, LIST(_TYPE_REFREF_ARG)) \
{ \
	boost::format format(fmtstr); \
	return detail::basic_format(format, LIST(_FORWARD_ARG)); \
}

_VARIADIC_EXPAND_1X(FORMAT_IMPL, , , , )
#undef FORMAT_IMPL

#else

// all other reasonably up-to-date compilers should support variadic templates
template <typename Arg, typename ... Args>
inline std::string format(const std::string& fmtstr, Arg&& arg, Args&& ... args)
{
	boost::format format(fmtstr);
	return detail::basic_format(format,
		std::forward<Arg>(arg), std::forward<Args>(args)...);
}

#endif
#endif // BOOST_FORMAT_HPP_
