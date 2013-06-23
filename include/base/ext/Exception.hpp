/**
 * @file Exception.hpp
 *
 */

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <exception>

/**
 * Helper to create new exception classes.
 * Exceptions should be described by their class, not their message.
 *
 * Using super::what() to suppress compiler warning about hiding
 * overloaded virtual function.
 */
#define PM_MAKE_EXCEPTION_CLASS(clazz, super) \
	class clazz : public super \
	{ public: \
		virtual ~clazz() throw () {} \
        using super::what; \
		virtual const char* what() throw () { return #clazz ; } \
	}

PM_MAKE_EXCEPTION_CLASS(Exception, std::exception);

#endif /* EXCEPTION_HPP_ */
