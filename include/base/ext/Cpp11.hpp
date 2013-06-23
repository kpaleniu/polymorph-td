/**
 * @file Cpp11.hpp
 * 
 * Header for c++11 hacks.
 */

#ifndef CPP11_HPP_
#define CPP11_HPP_


/* *** NO_CONSTEXPR ***
 *
 * Defined if constexpr doesn't exist.
 *
 *
 * *** NO_TEMPLATE_FRIENDS ***
 *
 * Defined if
 *
 * template <typename T>
 * struct A 
 * { 
 *     template <typename TT>
 *     friend class A<TT>;
 * };
 * 
 * doesn't work.
 *
 *
 * *** NO_TEMPLATE_VARARGS_INHERIT ***
 *
 * Defined if
 *
 * template <typename T>
 * struct A {};
 *
 * template <typename... Args>
 * struct B : A<Args>... {};
 *
 * doesn't work.
 *
 *
 * *** NO_THREAD_LOCAL ***
 *
 * Defined if thread_local doesn't exist.
 *
 *
 * *** NO_STD_SNPRINTF ***
 *
 * Defined if std::snprintf doesn't exist.
 */

#if defined(_MSC_VER)
#	define NO_CONSTEXPR
#	define NO_TEMPLATE_FRIENDS
#	define NO_TEMPLATE_VARARGS_INHERIT
#	define NO_THREAD_LOCAL
#	define NO_STD_SNPRINTF
#endif

#if defined(__APPLE__)
#   define NO_TEMPLATE_FRIENDS
#endif

#endif
