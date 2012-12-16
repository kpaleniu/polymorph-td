#ifndef RESOURCE_EXCEPTION
#define RESOURCE_EXCEPTION

#include <Exception.hpp>

class ResourceException : public Exception
{
public:
	ResourceException(std::string msg) : Exception(msg) {}
};

#endif /*RESOURCE_EXCEPTION*/
