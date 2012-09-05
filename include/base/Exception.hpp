/**
 * @file Exception.hpp
 *
 */

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <exception>

#include "text/String.hpp"

class Exception : public std::exception
{
public:
	Exception(text::String msg) throw ()
			: std::exception(), _msg(msg)
	{
		//
	}

	virtual ~Exception() throw ()
	{
		//
	}

	virtual const char *what() const throw ()
	{
		return _msg.c_str();
	}

private:
	text::String _msg;
};

#endif /* EXCEPTION_HPP_ */
