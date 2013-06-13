#include "concurrency/Mutex.hpp"

namespace polymorph { namespace concurrency {

Mutex::Mutex()
:	_mutex()
{
}

void Mutex::lock()
{
	Thread::interruptionPoint();
	_mutex.lock();
}

bool Mutex::tryLock()
{
	Thread::interruptionPoint();
	return _mutex.try_lock();
}

void Mutex::unlock()
{
	_mutex.unlock();
}

} }
