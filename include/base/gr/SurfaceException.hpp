/**
 * @file SurfaceException.hpp
 *
 */

#ifndef SURFACEEXCEPTION_HPP_
#define SURFACEEXCEPTION_HPP_

#include "Exception.hpp"

class SurfaceException : public Exception
{
public:
	SurfaceException(text::String msg) throw()
	: Exception(msg)
	{
		//
	}
};


#endif /* SURFACEEXCEPTION_HPP_ */
