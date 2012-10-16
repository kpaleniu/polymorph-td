/**
 * @file SystemActionQueue.hpp
 *
 */

#ifndef SYSTEM_ACTION_QUEUE_HPP
#define SYSTEM_ACTION_QUEUE_HPP

#include "stream/CyclicAutoIOStream.hpp"
#include "stream/StreamException.hpp"

#include "action/Action.hpp"

#include "concurrency/Mutex.hpp"

#include "Debug.hpp"

namespace sys {

template<typename ActionBase>
class SystemActionQueue
{
public:
	SystemActionQueue(size_t bufferSize);

	/*
	 *
	 */
	template<typename ActionData>
	void writeAction(const ActionBase &action,
	                 const ActionData &data);

	/**
	 * Pulls and performs an action from the queue.
	 *
	 * @param runner	Runner of the system.
	 * @returns 		true if more actions are in queue.
	 */
	template<typename Runner>
	void doAction(Runner &runner);

	bool isEmpty() const;

private:
	stream::CyclicAutoIOStream _runnerInput;
	concurrency::Mutex _rwMutex;
};

// Implementation

template<typename ActionBase>
template<typename ActionData>
void SystemActionQueue<ActionBase>::writeAction(const ActionBase &action,
                                    const ActionData &data)
{
	concurrency::MutexLockGuard lock(_rwMutex);

	if (_runnerInput.getSize()
	    - _runnerInput.bytesUnread()
	    < sizeof(action) + sizeof(data))
	{
		ERROR_OUT("SystemActionQueue", "Not enough space to write action\nSpace left: %1%\nAction size: %2%",
			(_runnerInput.getSize() - _runnerInput.bytesUnread()),
			(sizeof(action) + sizeof(data)));

		// Maybe the runner thread has died?
		throw stream::StreamException("Insufficient room to write action to stream");
	}

	VERBOSE_OUT("SystemActionQueue", "Writing action: %1%", &action);
	_runnerInput << &action << data;
}

template<typename ActionBase>
template<typename Runner>
void SystemActionQueue<ActionBase>::doAction(Runner &runner)
{
	concurrency::MutexLockGuard lock(_rwMutex);

	ActionBase *action;

	_runnerInput >> action;
	action->callAction(runner, _runnerInput);
}

template<typename ActionBase>
SystemActionQueue<ActionBase>::SystemActionQueue(size_t bufferSize)
: _runnerInput(bufferSize)
{
	//
}

template<typename ActionBase>
bool SystemActionQueue<ActionBase>::isEmpty() const
{
	return _runnerInput.bytesUnread() == 0;
}


}

#endif
