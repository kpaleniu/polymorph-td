/**
 * @file util.hpp
 *
 */

#ifndef STRING_HPP_
#define STRING_HPP_

#include <string>

namespace text {

typedef long string_hash;

string_hash intern(std::string str);
const std::string& get(string_hash hash);

void clearInterned();

}


#endif /* STRING_HPP_ */
