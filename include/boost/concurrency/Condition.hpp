/**
 * @file Condition.hpp
 *
 */

#ifndef CONDITION_HPP_
#define CONDITION_HPP_

#include "concurrency/Mutex.hpp"

#include <Time.hpp>
#include <NonCopyable.hpp>

#include <functional>

#include <boost/thread.hpp>

namespace concurrency {

/**
 * Condition class.
 * This class allows blocking until a condition is true.
 */
class Condition : NonCopyable
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
	void waitUntil(std::function<bool()> callable);
	/**
	 * Waits until the callable is true or when specified time has passed.
	 */
	void waitUntil(std::function<bool()> callable, TimeDuration timeout);

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

}


#endif /* CONDITION_HPP_ */
