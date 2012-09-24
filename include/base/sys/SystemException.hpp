/**
 * @file SystemException.hpp
 *
 */

#ifndef SYSTEM_EXCEPTION_HPP_
#define SYSTEM_EXCEPTION_HPP_

#include "Exception.hpp"
#include "text/String.hpp"


namespace sys {

/**
 * 
 * NOTE: A platform specific implementation needs to be supplied.
 */
class SystemException : public Exception
{
public:

	/**
	 * Platform specific error code type.
	 * Windows - DWORD (unsigned long)
	 */
	typedef unsigned long error_type;

	/**
	 * @param code Platorm specific error code.
	 * @param msg Additional error message (prepended to system error message).
	 */
	explicit SystemException(error_type code, const char* msg = "");

	/**
	 * @return Error code given to constructor.
	 */
	error_type code() const { return _code; }

	virtual const char* what() const;

private:
	error_type _code;
	mutable text::String _error;
};

}	// namespace sys

#endif /* SYSTEM_EXCEPTION_HPP_ */
