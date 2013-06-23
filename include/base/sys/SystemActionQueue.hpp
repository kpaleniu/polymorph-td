#ifndef SYSTEM_ACTION_QUEUE_HPP
#define SYSTEM_ACTION_QUEUE_HPP

#include <concurrency/Condition.hpp>

#include <Exception.hpp>
#include <Debug.hpp>

#include <functional>
#include <vector>

namespace polymorph { namespace sys {

PM_MAKE_EXCEPTION_CLASS(ActionQueueException, Exception);

template<typename Runner>
class SystemActionQueue
{
public:
	SystemActionQueue(size_t actionCapacity);

	SystemActionQueue(SystemActionQueue&& actionQueue);

	typedef std::function<void (Runner&)> RunnerAction;

	// May throw ActionQueueException if adding would overflow buffer.
	void pushAction(RunnerAction action);

	void doAction(Runner& runner);

	bool isEmpty() const;

	concurrency::Condition& pushCondition() const;

private:
	std::vector<RunnerAction> _runnerInput;

	size_t _writeIndex;
	size_t _readIndex;
	size_t _unreadActions;

	mutable concurrency::Condition _pushCondition;
};

} }

#include "sys/SystemActionQueue.inl"

#endif
