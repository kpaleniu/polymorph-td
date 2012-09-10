/**
 * @file Mutex.cpp
 *
 */

#include "sys/Mutex.hpp"

namespace sys {

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

}
