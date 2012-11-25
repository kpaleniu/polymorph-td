/**
 * @file Exception.hpp
 *
 */

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <exception>
#include <string>

class Exception : public std::exception
{
public:
	Exception(std::string msg) throw ()
			: std::exception(), _msg(msg)
	{
	}

	virtual ~Exception() throw ()
	{
	}

	virtual const char* what() const throw ()
	{
		return _msg.c_str();
	}

private:
	std::string _msg;
};

#endif /* EXCEPTION_HPP_ */
