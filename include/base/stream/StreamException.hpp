/**
 * @file StreamException.hpp
 *
 */

#ifndef STREAMEXCEPTION_HPP_
#define STREAMEXCEPTION_HPP_

#include "Exception.hpp"

namespace stream {

class StreamException : public Exception
{
public:
	StreamException(std::string msg) throw ()
			: Exception(msg)
	{
	}
};

}


#endif /* STREAMEXCEPTION_HPP_ */
