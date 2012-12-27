/**
 * @file util.cpp
 *
 */

#include "text/util.hpp"

#include <Debug.hpp>
#include <Assert.hpp>

#include <map>

namespace text {

namespace {

std::map<string_hash, std::string> interned;

}

string_hash intern(std::string str)
{
	string_hash rHash = hash(str.c_str());

#ifdef _DEBUG
	if (interned.count(rHash) != 0)
	{
		ASSERT(interned[rHash] == str, "Hash collision");
		INFO_OUT("StringHash", "WARNING: re-hashing string");
	}
#endif

	interned[rHash] = str;

	return rHash;
}

const std::string& get(string_hash hash)
{
	ASSERT(interned.count(hash) != 0, "No string with that hash");

	return interned[hash];
}

void clearInterned()
{
	interned.clear();
}

}

