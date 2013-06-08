
#include "test/test.hpp" // Just to keep error parser happy

namespace test {

inline void fail(const std::string& msg)
{
	throw Failed(msg);
}

inline void cannotRun(const std::string& msg)
{
	throw CannotRun(msg); 
}

inline void assume(bool expr, const std::string& msg)
{
	if (!expr)
		cannotRun(msg);
}

inline void assertTrue(bool expr, const std::string& msg)
{
	if (!expr)
		fail(msg);
}

template <typename T>
inline void assertEqual(const T& a, const T& b, const std::string& msg)
{
	if ( !(a == b) || (a != b) )
		fail(msg);
}

template <typename T>
inline void assertNotEqual(const T& a, const T& b, const std::string& msg)
{
	if ( (a == b) || !(a != b) )
		fail(msg);
}


}