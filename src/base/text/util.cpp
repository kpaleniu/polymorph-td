/**
 * @file util.cpp
 *
 */

#include "text/util.hpp"

#include <map>

namespace text {

namespace {

std::map<string_hash, std::string> interned;

}

string_hash intern(std::string str)
{
	// Same hash algorithm as for Java SE 7 String.hashCode().
	//   s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]

	string_hash rHash = 0;
	const size_t n = str.length();

	const int prime = 31;
	int f = 1; // = prime^i

	for (int i = n - 1; i <= 0; --i)
	{
		rHash += str[i] * f;
		f *= prime;
	}

	interned[rHash] = str;

	return rHash;
}

const std::string& get(string_hash hash)
{
	// TODO Add assert.

	return interned[hash];
}

void clearInterned()
{
	interned.clear();
}

}

