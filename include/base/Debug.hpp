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

#define DEBUG_OUT_UNIT(unit, msg) \
	if (unit)\
	DEBUG_OUT(msg);

#define BUFFER_UNIT 					1
#define CYCLIC_AUTO_IO_STREAM_UNIT 		1
#define CYCLIC_AUTO_OUTPUT_STREAM_UNIT	1

#endif /* DEBUG_HPP_ */
