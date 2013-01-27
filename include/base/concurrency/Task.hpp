/**
 * @file Task.hpp
 *
 */

#ifndef TASK_HPP_
#define TASK_HPP_

#include "concurrency/Mutex.hpp"

namespace concurrency {

template<typename R>
class Task
{
public:
	Task();

	bool hasResult() const;
	R& waitForResult() const;

protected:
	R* _result;
	mutable Condition _doneCondition;
};

// Implementation:

template<typename R>
Task<R>::Task()
:	_result(nullptr)
{}

template<typename R>
bool Task<R>::hasResult() const
{
	if (_doneCondition.mutex().tryLock())
	{
		bool hasRes = (_result != nullptr);
		_doneCondition.mutex().unlock();

		return hasRes;
	}

	// Task is running.
	return false;
}

template<typename R>
R& Task<R>::waitForResult() const
{
	_doneCondition.waitUntil([this] -> bool {return _result != nullptr});
	return *_result;
}

}

#endif /* TASK_HPP_ */
