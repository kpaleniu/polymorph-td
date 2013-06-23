#include "sys/SystemActionQueue.hpp"

#include <Assert.hpp>

namespace polymorph { namespace sys {

template <typename Runner>
SystemActionQueue<Runner>::SystemActionQueue(size_t actionCapacity)
:	_runnerInput(actionCapacity, RunnerAction()),
 	_writeIndex(0),
 	_readIndex(0),
 	_unreadActions(0),
 	_pushCondition()
{
}

template <typename Runner>
SystemActionQueue<Runner>::SystemActionQueue(SystemActionQueue&& actionQueue)
:	_runnerInput(std::move(actionQueue._runnerInput)),
 	_writeIndex(actionQueue._writeIndex),
 	_readIndex(actionQueue._readIndex),
 	_unreadActions(actionQueue._unreadActions),
 	_pushCondition()
{
}

template <typename Runner>
void SystemActionQueue<Runner>::pushAction(RunnerAction action)
{
	{
		concurrency::MutexLockGuard lock(_pushCondition.mutex());

		if (_unreadActions >= _runnerInput.size())
			throw ActionQueueException();

		_runnerInput[_writeIndex++] = action;
		_writeIndex %= _runnerInput.size();

		++_unreadActions;
	}

	_pushCondition.notifyAll();
}

template <typename Runner>
void SystemActionQueue<Runner>::doAction(Runner& runner)
{
	RunnerAction action;

	{
		concurrency::MutexLockGuard lock(_pushCondition.mutex());

		ASSERT(_unreadActions > 0, "Trying to read empty action queue.");

		action = _runnerInput[_readIndex++];

		_readIndex %= _runnerInput.size();
		--_unreadActions;
	}

	action(runner);
}

template <typename Runner>
bool SystemActionQueue<Runner>::isEmpty() const
{
	return _unreadActions == 0;
}

template<typename Runner>
concurrency::Condition& SystemActionQueue<Runner>::pushCondition() const
{
	return _pushCondition;
}


} }