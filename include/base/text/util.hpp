/**
 * @file util.hpp
 *
 */

#ifndef STRING_HPP_
#define STRING_HPP_

#include <string>
#include <Cpp11.hpp>

namespace text {

typedef long string_hash;

string_hash intern(std::string str);
const std::string& get(string_hash hash);

void clearInterned();


template <typename SourceChar, typename TargetChar>
std::basic_string<TargetChar> convert(const std::basic_string<SourceChar>& str)
{
	std::basic_string<TargetChar> rString;
	rString.assign(str.begin(), str.end());

	return rString;
}

// Compile-time constant expressions.

#ifndef NO_CONSTEXPR

inline constexpr size_t strLen(const char* str)
{
	return *str ? 1 + strLen(str + 1) : 0;
}

inline constexpr unsigned long power(unsigned long base, std::size_t exp)
{
	return exp != 0 ? base * power(base, exp - 1) : 1;
}

namespace detail {

/**
 * Prime used in hashing algorithm.
 */
constexpr unsigned long HASH_PRIME = 31;

/**
 * Recursive hashing algorithm.
 *
 * Same hash algorithm as for Java SE 7 String.hashCode().
 *   s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]
 *
 * f(n) = p ^ n, p = HASH_PRIME
 * s(n) = str[n]
 *
 * hash = sum [i = 0 .. len(str)-1] ( f(len(str)-1 - i) + s(i) )
 *
 */
inline constexpr string_hash hash_it(const char* str, size_t i, size_t strSize)
{
	return str[i] * power(HASH_PRIME, strSize - 1 - i) + (i == strSize - 1 ? 0 : hash_it(str, i + 1, strSize));
}

}


inline constexpr string_hash hash(const char* str)
{
	return detail::hash_it(str, 0, strLen(str));
}

#else

inline size_t strLen(const char* str)
{
	return *str ? 1 + strLen(str + 1) : 0;
}

inline unsigned long power(unsigned long base, std::size_t exp)
{
	return exp != 0 ? base * power(base, exp - 1) : 1;
}

namespace detail {

/**
 * Prime used in hashing algorithm.
 */
#define HASH_PRIME 31

/**
 * Recursive hashing algorithm.
 *
 * Same hash algorithm as for Java SE 7 String.hashCode().
 *   s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]
 *
 * f(n) = p ^ n, p = HASH_PRIME
 * s(n) = str[n]
 *
 * hash = sum [i = 0 .. len(str)-1] ( f(len(str)-1 - i) + s(i) )
 *
 */
inline string_hash hash_it(const char* str, size_t i, size_t strSize)
{
	return str[i] * power(HASH_PRIME, strSize - 1 - i) + (i == strSize - 1 ? 0 : hash_it(str, i + 1, strSize));
}

}


inline string_hash hash(const char* str)
{
	return detail::hash_it(str, 0, strLen(str));
}

#endif

}


#endif /* STRING_HPP_ */
