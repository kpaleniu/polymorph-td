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

#include <condition_variable>


namespace polymorph { namespace concurrency {

class Condition : NonCopyable
{
public:
	Condition();

	void waitUntil(std::function<bool()> callable);
	bool waitUntil(std::function<bool()> callable, TimeDuration timeout);

	void notifyAll();

	Mutex& mutex();

private:
	Mutex _mutex;
	std::condition_variable _cond;
};

} }


#endif
