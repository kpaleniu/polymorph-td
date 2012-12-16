/**
 * @file Mutex.hpp
 *
 */

#ifndef MUTEX_HPP_
#define MUTEX_HPP_

#include <NonCopyable.hpp>

#include <boost/thread.hpp>


namespace concurrency {

class Mutex : NonCopyable
{
public:
	Mutex();

	void lock();
	bool tryLock();
	void unlock();

public:
	boost::mutex& boostMutex();

private:
	boost::mutex _mutex;
};

class MutexLockGuard : NonCopyable
{
public:
	MutexLockGuard(Mutex& mutex)
	:	_mutex(mutex),
	 	_active(true)
	{
		_mutex.lock();
	}

	MutexLockGuard(MutexLockGuard&& other)
	:	_mutex(other._mutex),
	 	_active(true)
	{
		other._active = false;
	}

	~MutexLockGuard()
	{
		if (_active)
			_mutex.unlock();
	}

private:
	Mutex& _mutex;
	bool _active;
};

}


#endif /* MUTEX_HPP_ */
