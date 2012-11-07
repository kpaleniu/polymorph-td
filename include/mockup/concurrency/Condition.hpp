/**
 * @file Condition.hpp
 *
 */

#ifndef CONDITION_HPP_
#define CONDITION_HPP_

#include "concurrency/Mutex.hpp"
#include "NonCopyable.hpp"

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
	 * Waits until the callable returns true.
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
};

// Mockup implementation

// TODO

}


#endif /* CONDITION_HPP_ */
