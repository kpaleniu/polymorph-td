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
	 * @param msg Additional error message.
	 */
	explicit SystemException(error_type code, const char* msg = "") throw();

	virtual ~SystemException() throw() {};

	/**
	 * @return Error code given to constructor.
	 */
	error_type code() const { return _code; }

	/**
	 * @return Additional error message passed in constructor prepended
	 *   to the error message associated with the error code.
	 */
	virtual const char* what() const throw();

private:
	error_type _code;
	mutable text::String _error;
};

}	// namespace sys

#endif /* SYSTEM_EXCEPTION_HPP_ */
