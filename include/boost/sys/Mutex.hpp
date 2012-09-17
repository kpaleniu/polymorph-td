/**
 * @file Mutex.hpp
 *
 */

#ifndef MUTEX_HPP_
#define MUTEX_HPP_

#include "NonCopyable.hpp"
#include "sys/Time.hpp"

#include <boost/thread.hpp>


namespace sys {

class Mutex
{
public:
	void lock();
	bool tryLock();
	void unlock();

private:
	boost::mutex _mutex;
};

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

}


#endif /* MUTEX_HPP_ */
