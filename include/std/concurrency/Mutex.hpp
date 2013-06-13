#ifndef STD_MUTEX_HPP_
#define STD_MUTEX_HPP_

#include "concurrency/Thread.hpp"

#include <NonCopyable.hpp>

#include <mutex>


namespace polymorph { namespace concurrency {

class Mutex : NonCopyable
{
public:
	Mutex();

	void lock();
	bool tryLock();
	void unlock();

public:
	std::mutex _mutex;
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

} }


#endif
