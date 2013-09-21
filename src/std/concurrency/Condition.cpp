
#include "concurrency/Condition.hpp"

#include <Scoped.hpp>

namespace polymorph { namespace concurrency {

Condition::Condition()
:	_mutex(),
 	_cond()
{
}

void Condition::notifyAll()
{
	_cond.notify_all();
}

Mutex& Condition::mutex()
{
	return _mutex;
}

void Condition::waitUntil(std::function<bool()> callable)
{
	Thread::interruptionPoint();

	Scoped conditionSetScope
	(
		[this]	{ Thread::setCondition(&_cond); },
		[]		{ Thread::setCondition(nullptr);} 
	);

	{
		std::unique_lock<std::mutex> lock(_mutex._mutex);
		_cond.wait
		(
			lock, 
			[&]() -> bool
			{
				Thread::interruptionPoint();
				return callable();
			}
		);
	}
}

bool Condition::waitUntil(std::function<bool()> callable,
                          TimeDuration timeout)
{
	Scoped conditionSetScope
	(
		[this]	{ Thread::setCondition(&_cond); },
		[]		{ Thread::setCondition(nullptr);} 
	);

	{
		std::unique_lock<std::mutex> lock(_mutex._mutex);

		return _cond.wait_for
		(
			lock, 
			timeout._std__timeDuration, 
			[&]() -> bool
			{
				Thread::interruptionPoint();
				return callable();
			}
		);
	}
}

} }
