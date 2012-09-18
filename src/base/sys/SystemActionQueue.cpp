/**
 * @file SystemActionQueue.cpp
 *
 */


#include "sys/SystemActionQueue.hpp"


namespace sys {

SystemActionQueue::SystemActionQueue(size_t bufferSize)
: _runnerInput(bufferSize)
{
	//
}

void SystemActionQueue::doAction()
{
	sys::MutexLockGuard lock(_rwMutex);

	action::Action *action;

	_runnerInput >> action;

	DEBUG_OUT("Reading action: " << action);

	action->callAction(_runnerInput);
}

bool SystemActionQueue::isEmpty() const
{
	return _runnerInput.bytesUnread() == 0;
}

}

