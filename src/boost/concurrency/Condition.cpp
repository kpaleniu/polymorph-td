/**
 * @file Condition.cpp
 *
 */


#include <concurrency/Condition.hpp>

namespace concurrency {

Condition::Condition()
:	_mutex(),
 	_cond()
{
}

void Condition::notifyAll()
{
	_cond.notify_all();
}

Mutex &Condition::mutex()
{
	return _mutex;
}

}

void concurrency::Condition::waitUntil(std::function<bool()> callable)
{
	boost::unique_lock<boost::mutex> lock(_mutex.boostMutex());
	_cond.wait(lock, callable);
}

void concurrency::Condition::waitUntil(std::function<bool()> callable,
                                       TimeDuration timeout)
{
	boost::unique_lock<boost::mutex> lock(_mutex.boostMutex());
	boost::system_time const boostTimeout = boost::get_system_time() + timeout.timeDuration;
	_cond.timed_wait(lock, boostTimeout, callable);
}
