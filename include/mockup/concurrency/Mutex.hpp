/**
 * @file Mutex.hpp
 *
 */

#ifndef MUTEX_HPP_
#define MUTEX_HPP_

#include "NonCopyable.hpp"

namespace concurrency {

/**
 * Platform specific mutex class.
 */
class Mutex
{
public:
	/**
	 * Locks the mutex.
	 */
	void lock();
	/**
	 * Tries to lock the mutex.
	 *
	 * @returns	True if succesful, else false.
	 */
	bool tryLock();
	/**
	 * Unlocks the mutex.
	 */
	void unlock();
};

/**
 * Lock guard for mutex.
 * This implementation is non-platform specific.
 */
class MutexLockGuard : NonCopyable
{
public:
	MutexLockGuard(Mutex &mutex)
	: _mutex(mutex)
	{
		_mutex.lock();
	}

	~MutexLockGuard()
	{
		_mutex.unlock();
	}

private:
	Mutex &_mutex;
};

// Mockup implementation

// TODO

}


#endif /* MUTEX_HPP_ */
