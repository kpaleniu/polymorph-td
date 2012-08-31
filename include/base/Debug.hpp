/**
 * @file Debug.hpp
 *
 */

#ifndef DEBUG_HPP_
#define DEBUG_HPP_

#include <iostream>

#ifdef _DEBUG
#	define DEBUG_OUT(msg) std::clog << msg << std::endl;
#else
#	define DEBUG_OUT(msg) (void 0)
#endif


#endif /* DEBUG_HPP_ */
