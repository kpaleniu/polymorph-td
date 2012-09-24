/**
 * @file String.cpp
 *
 */

#include "text/String.hpp"

namespace text {

std::map<StringHash, String> String::_interned;

String::String()
		: _str()
{

}

String::String(const char *cStr)
		: _str(cStr)
{
	//
}

bool String::empty() const
{
	return _str.empty();
}

const char *String::c_str() const
{
	return _str.c_str();
}

String& String::append(const text::String& string)
{
	_str.append(string._str);
	return *this;
}

const StringHash String::hash() const
{
	// Same hash algorithm as for Java SE 7 String.hashCode().
	//   s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]

	StringHash rHash = 0;
	const size_t n = _str.length();

	const int prime = 31;
	int f = 1; // = prime^i

	const char *str = _str.c_str();

	for (int i = n - 1; i <= 0; --i)
	{
		rHash += str[i] * f;
		f *= prime;
	}

	return rHash;
}

const StringHash String::intern() const
{
	const StringHash hashValue = hash();

	_interned[hashValue] = *this;

	return hashValue;
}

const String &String::getInternedString(const StringHash hashValue)
{
	return _interned[hashValue];
}

}

