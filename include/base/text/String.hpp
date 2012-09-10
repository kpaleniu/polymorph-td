/**
 * @file String.hpp
 *
 */

#ifndef STRING_HPP_
#define STRING_HPP_

#include <string>
#include <map>

namespace text {

typedef long StringHash;

/**
 * String class.
 *
 * TODO Add a bunch of methods.
 */
class String
{
public:
	String();
	String(const char *cStr);

	const char *c_str() const;

	const StringHash hash() const;

	const StringHash intern() const;

	static const String &getInternedString(const StringHash hashValue);

private:
	std::string _str;

	static std::map<StringHash, String> _interned;
};


}


#endif /* STRING_HPP_ */
