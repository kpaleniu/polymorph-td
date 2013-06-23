
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
    /*
     * Clang does not seem to support thread_local keyword. In GCC
     * the support only came with 4.8. Therefore fallback to __thread
     * keyword.
     * 
     * Caution! result of __thread keyword is highly platform,
     * compiler and standard library dependant.
     */
#   if defined(__APPLE__) || ( __GNUC__ <= 4 && __GNUC_MINOR__ < 8 )
        static __thread char buffer[FORMAT_BUFFER_SIZE];
#   else
        static thread_local char buffer[FORMAT_BUFFER_SIZE];
#   endif
#endif
	
#ifdef NO_STD_SNPRINTF
#	ifdef _MSC_VER
		sprintf_s(buffer,
				  FORMAT_BUFFER_SIZE,
				  fmtstr.c_str(),
				  std::forward<Arg>(arg),
				  std::forward<Args>(args)...);
#	else
		std::sprintf(buffer, 
					 fmtstr.c_str(), 
					 std::forward<Arg>(arg),
					 std::forward<Args>(args)...);
#	endif
#else
	std::snprintf(buffer, 
				  FORMAT_BUFFER_SIZE,
				  fmtstr.c_str(), 
				  std::forward<Arg>(arg),
				  std::forward<Args>(args)...);
#endif

	return buffer;
}

#undef FORMAT_BUFFER_SIZE


#endif
