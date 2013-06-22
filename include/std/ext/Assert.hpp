#ifndef STD_ASSERT_HPP_
#define STD_ASSERT_HPP_

#include <cassert>


/**
 * If expr evaluates to false an assertion handler is triggered,
 * which by default prints relevant information to std::cerr.
 * Disabled by defining NDEBUG.
 */
#define ASSERT(expr, msg) assert(expr && msg)

/**
 * Similar to ASSERT, except that the expression is
 * always evaluated. Useful when there are desirable
 * side-effects to the expression.
 */
#ifdef NDEBUG
#	define VERITY(expr) expr
#else
#	define VERIFY(expr) assert(expr)
#endif


#endif
