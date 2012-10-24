/**
 * @file GraphicsException.hpp
 *
 */

#ifndef GRAPHICSEXCEPTION_HPP_
#define GRAPHICSEXCEPTION_HPP_

#include "Exception.hpp"

class GraphicsException : public Exception
{
public:
	GraphicsException(std::string msg) throw()
	: Exception(msg)
	{
	}
};

#endif /* GRAPHICSEXCEPTION_HPP_ */
