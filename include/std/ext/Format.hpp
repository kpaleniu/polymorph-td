
#ifndef STD_FORMAT_HPP_
#define STD_FORMAT_HPP_

#include <Cpp11.hpp>

#include <string>
#include <cstdio>

inline std::string format(const std::string& fmtstr)
{
	return fmtstr;
}


#define FORMAT_BUFFER_SIZE 256

template <typename Arg, typename... Args>
inline std::string format(const std::string& fmtstr, Arg&& arg, Args&& ... args)
{
#ifdef NO_THREAD_LOCAL
#	ifdef _MSC_VER
		__declspec( thread ) static char buffer[FORMAT_BUFFER_SIZE];
#	else
		char buffer[FORMAT_BUFFER_SIZE];
#	endif
#else
	thread_local static char buffer[FORMAT_BUFFER_SIZE];
#endif
	
#ifdef NO_STD_SNPRINTF
	std::sprintf(buffer, 
				 fmtstr.c_str(), 
				 std::forward<Arg>(arg),
				 std::forward<Args...>(args)...);
#else
	std::snprintf(buffer, 
				  FORMAT_BUFFER_SIZE,
				  fmtstr.c_str(), 
				  std::forward<Arg>(arg),
				  std::forward<Args...>(args)...);
#endif

	return buffer;
}

#undef FORMAT_BUFFER_SIZE


#endif
