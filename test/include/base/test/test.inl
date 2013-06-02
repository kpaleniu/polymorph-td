
#include "test/test.hpp" // Just to keep error parser happy

namespace test {

inline void fail()
{
	throw Failed(); 
}

inline void cannotRun()
{
	throw CannotRun(); 
}

inline void assume(bool expr)
{
	if (!expr)
		cannotRun();
}

inline void assertTrue(bool expr)
{
	if (!expr)
		fail();
}

template <typename T>
inline void assertEqual(const T& a, const T& b)
{
	if ( !(a == b) || (a != b) )
		fail();
}

template <typename T>
inline void assertNotEqual(const T& a, const T& b)
{
	if ( (a == b) || !(a != b) )
		fail();
}


}