/**
 * @file Mutex.cpp
 *
 */

#include "concurrency/Mutex.hpp"

namespace concurrency {

void Mutex::lock()
{
	_mutex.lock();
}

bool Mutex::tryLock()
{
	return _mutex.try_lock();
}

void Mutex::unlock()
{
	_mutex.unlock();
}

boost::mutex &Mutex::boostMutex()
{
	return _mutex;
}

}
