/**
 * @file SystemActionQueue.hpp
 *
 */

#ifndef SYSTEM_ACTION_QUEUE_HPP
#define SYSTEM_ACTION_QUEUE_HPP

#include "stream/CyclicAutoIOStream.hpp"
#include "stream/StreamException.hpp"

#include "action/Action.hpp"

#include "sys/Mutex.hpp"

#include "Debug.hpp"

namespace sys {

class SystemActionQueue
{
public:
	SystemActionQueue(size_t bufferSize);

	/*
	 *
	 */
	template<typename ActionData>
	void writeAction(const action::Action &action,
	                 const ActionData &data);

	/**
	 * Pulls and performs an action from the queue.
	 *
	 * @returns true if more actions are in queue.
	 */
	void doAction();

	bool isEmpty() const;

private:
	stream::CyclicAutoIOStream _runnerInput;
	Mutex _rwMutex;
};

// Implementation

template<typename ActionData>
void SystemActionQueue::writeAction(const action::Action &action,
                                    const ActionData &data)
{
	sys::MutexLockGuard lock(_rwMutex);

	if (_runnerInput.getSize()
	    - _runnerInput.bytesUnread()
	    < sizeof(action) + sizeof(data))
	{
		DEBUG_OUT_UNIT(SYSTEM_ACTION_QUEUE_UNIT,
		               "Not enough space to write action");
		DEBUG_OUT_UNIT(SYSTEM_ACTION_QUEUE_UNIT,
		               "Space left: " << (_runnerInput.getSize() - _runnerInput.bytesUnread()));
		DEBUG_OUT_UNIT(SYSTEM_ACTION_QUEUE_UNIT,
		               "Action size: " << (sizeof(action) + sizeof(data)));

		// Maybe the runner thread has died?
		throw stream::StreamException("Insufficient room to write action to stream");
	}

	DEBUG_OUT_UNIT(SYSTEM_ACTION_QUEUE_UNIT,
	               "Writing action: " << &action);

	_runnerInput << &action << data;
}

}

#endif
