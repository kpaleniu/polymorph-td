/**
 * @file SystemActionQueue.hpp
 *
 */

#ifndef SYSTEM_ACTION_QUEUE_HPP
#define SYSTEM_ACTION_QUEUE_HPP

#include "stream/StreamException.hpp"

#include "concurrency/Mutex.hpp"

#include "Debug.hpp"

#include <functional>
#include <vector>

namespace sys {



template<typename Runner>
class SystemActionQueue
{
public:
	SystemActionQueue(size_t actionCapacity);

	SystemActionQueue(SystemActionQueue&& actionQueue);

	typedef std::function<void (Runner&)> RunnerAction;

	void pushAction(RunnerAction action);

	/**
	 * Pulls and performs an action from the queue.
	 *
	 * @param runner	Runner of the system.
	 * @returns 		true if more actions are in queue.
	 */
	void doAction(Runner& runner);

	bool isEmpty() const;

private:
	std::vector<RunnerAction> _runnerInput;

	size_t _writeIndex;
	size_t _readIndex;
	size_t _unreadActions;

	mutable concurrency::Mutex _rwMutex;
};

// Implementation

template<typename Runner>
SystemActionQueue<Runner>::SystemActionQueue(size_t actionCapacity)
:	_runnerInput(actionCapacity, RunnerAction()),
 	_writeIndex(0),
 	_readIndex(0),
 	_unreadActions(0),
 	_rwMutex()
{
}

template<typename Runner>
SystemActionQueue<Runner>::SystemActionQueue(SystemActionQueue&& actionQueue)
:	_runnerInput(std::move(actionQueue._runnerInput)),
 	_writeIndex(actionQueue._writeIndex),
 	_readIndex(actionQueue._readIndex),
 	_unreadActions(actionQueue._unreadActions),
 	_rwMutex() // Can't move mutex.
{
}

template<typename Runner>
void SystemActionQueue<Runner>::pushAction(RunnerAction action)
{
	concurrency::MutexLockGuard lock(_rwMutex);

	if (_unreadActions >= _runnerInput.size())
	{
		// Should resize ?
		throw stream::StreamException("SystemActionQueue out of space");
	}

	_runnerInput[_writeIndex++] = action;
	_writeIndex %= _runnerInput.size();

	++_unreadActions;
}

template<typename Runner>
void SystemActionQueue<Runner>::doAction(Runner& runner)
{
	RunnerAction action;

	{
		concurrency::MutexLockGuard lock(_rwMutex);

		if (_unreadActions == 0)
		{
			throw stream::StreamException("SystemActionQueue is empty");
		}

		action = _runnerInput[_readIndex++];

		_readIndex %= _runnerInput.size();
		--_unreadActions;
	}

	action(runner);
}

template<typename Runner>
bool SystemActionQueue<Runner>::isEmpty() const
{
	concurrency::MutexLockGuard lock(_rwMutex);
	return _unreadActions == 0;
}


}

#endif
