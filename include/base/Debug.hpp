/**
 * @file Debug.hpp
 *
 */

#ifndef DEBUG_HPP_
#define DEBUG_HPP_

#include "concurrency/Thread.hpp"
#include "concurrency/Mutex.hpp"
#include <iostream>

namespace debug {

static concurrency::Mutex __outMutex;

}

#ifdef _DEBUG
#	define DEBUG_OUT(msg) \
{   concurrency::MutexLockGuard __lock(debug::__outMutex); \
	std::clog 	<< __FILE__ \
				<< "@" \
				<< __LINE__ \
				<< " thread=" \
				<< concurrency::Thread::getCurrentID() \
				<< "\n" \
				<< msg << std::endl; }
#else
#	define DEBUG_OUT(msg) (void 0)
#endif

#define DEBUG_OUT_UNIT(unit, msg) \
	if (unit)\
	{DEBUG_OUT(msg);}

#define BUFFER_UNIT 					1
#define CYCLIC_AUTO_IO_STREAM_UNIT 		1
#define CYCLIC_AUTO_OUTPUT_STREAM_UNIT	1
#define THREAD_UNIT						1
#define SYSTEM_ACTION_QUEUE_UNIT		1

#endif /* DEBUG_HPP_ */
