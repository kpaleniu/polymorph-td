#pragma once
#ifndef BOOST_ASSERT_HPP_
#define BOOST_ASSERT_HPP_

// NOTE: override the default boost assert stream on MSVC
#ifdef _MSC_VER
#define BOOST_ASSERT_MSG_OSTREAM std::cout
#endif

#include <boost/assert.hpp>


/**
 * If expr evaluates to false an assertion handler is triggered,
 * which by default prints relevant information to std::cerr.
 * Disabled by defining NDEBUG.
 */
#define ASSERT(expr, msg) BOOST_ASSERT_MSG(expr, msg)

/**
 * Similar to ASSERT, except that the expression is
 * always evaluated. Useful when there are desirable
 * side-effects to the expression.
 */
#define VERIFY(expr) BOOST_VERIFY(expr)


#endif  // BOOST_ASSERT_HPP_
