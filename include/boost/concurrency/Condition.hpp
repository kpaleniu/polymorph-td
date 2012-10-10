/**
 * @file Condition.hpp
 *
 */

#ifndef CONDITION_HPP_
#define CONDITION_HPP_

#include "concurrency/Mutex.hpp"
#include <boost/thread.hpp>

namespace concurrency {

/**
 * Condition class.
 * This class allows blocking until a condition is true.
 */
class Condition
{
public:
	/**
	 * Constructor.
	 */
	Condition();

	/**
	 * Waits until the callable is true.
	 * This is checked at notification.
	 *
	 * @param callable	A callable object that returns a bool.
	 */
	template<typename BoolCallable>
	void waitUntil(BoolCallable callable);

	/**
	 * Notifies that the condition has been updated.
	 */
	void notifyAll();

	/**
	 * Access to the state update mutex.
	 * This should be locked when updating the condition state,
	 * but not when calling notifyAll.
	 */
	Mutex &mutex();

private:
	Mutex _mutex;
	boost::condition_variable _cond;
};

// Template implementation

template<typename BoolCallable>
void Condition::waitUntil(BoolCallable callable)
{
	boost::unique_lock<boost::mutex> lock(_mutex.boostMutex());
	while (!callable())
		_cond.wait(lock);
}


}


#endif /* CONDITION_HPP_ */
