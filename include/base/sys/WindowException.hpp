/**
 * @file WindowException.hpp
 *
 */

#ifndef WINDOWEXCEPTION_HPP_
#define WINDOWEXCEPTION_HPP_

#include "Exception.hpp"

namespace sys {

class WindowException : public Exception
{
public:
	WindowException(text::String msg) throw ()
			: Exception(msg)
	{
		//
	}
};

}
#endif /* WINDOWEXCEPTION_HPP_ */
