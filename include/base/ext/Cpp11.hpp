/**
 * @file Cpp11.hpp
 * 
 * Header for c++11 hacks.
 */

#ifndef CPP11_HPP_
#define CPP11_HPP_

#if defined(_MSC_VER)
#	define NO_CONSTEXPR
#	define NO_TEMPLATE_FRIENDS
#	define NO_TEMPLATE_VARARGS_INHERIT
#	define NO_THREAD_LOCAL
#	define NO_STD_SNPRINTF
#endif

#endif
