#include "sys/System.hpp"


namespace polymorph { namespace sys {

template <typename Runner>
System<Runner>::System(const TimeDuration& sync,
                       size_t bufferSize,
					   typename Runner::ConstructionArgs&& runnerConstructionArgs)
:	Thread(),
	_runnerConstructionArgs(std::move(runnerConstructionArgs)),
	_actions(bufferSize),
	_runnerAccess(nullptr),
	_sync(sync),
	_started(false),
	_startupCond()
{
}

template <typename Runner>
System<Runner>::System(System&& system)
:	Thread(std::move(system)),
	_runnerConstructionArgs(std::move(system._runnerConstructionArgs)),
	_actions(std::move(system._actions)),
	_runnerAccess(system._runnerAccess.load()),
	_sync(system._sync),
	_started(system._started),
	_startupCond() // Conditions can't be moved.
{
}

template <typename Runner>
System<Runner>::~System()
{
}

template <typename Runner>
void System<Runner>::waitForStartup()
{
	_startupCond.waitUntil( [this]() -> bool {return this->_started;} );
}

template <typename Runner>
SystemActionQueue<Runner>& System<Runner>::actionQueue()
{
	if (getThreadState() == ThreadState::EXITED)
		throw SystemDeadException();

	return _actions;
}

template <typename Runner>
void System<Runner>::threadMain()
{
	static const char* TAG = "System";

	Runner runner( std::move(_runnerConstructionArgs), *this );

	Scoped accessScope([&]{ _runnerAccess = &runner; },
	                   [&]{ _runnerAccess = nullptr; });


	{
		concurrency::MutexLockGuard lock(_startupCond.mutex());
		_started = true;
	}
	_startupCond.notifyAll();

	//---------------- Main system loop ----------------//

	TimeDuration lastDT = TimeDuration::millis(0);

	DEBUG_OUT(TAG, "Started thread main loop");
	for (;;)
	{
		TimeStamp t0 = TimeStamp::now();

		//---------------- Runner updating ----------------//

		{
			// auto profileBlock = profiler::ThreadProfiler::profileBlock(updateName);

			if (!runner.update(lastDT))
				return;
		}

		//---------------- Action updating ----------------//

		TimeDuration realDT = TimeDuration::between(t0, TimeStamp::now());
		TimeDuration waitDuration = _sync - realDT;

		while ( _actions.pushCondition().waitUntil([&]{ return !_actions.isEmpty(); },
		                                           waitDuration) )
		{
			{
				// auto profileBlock = profiler::ThreadProfiler::profileBlock(actionName);
				_actions.doAction(runner);
			}

			realDT = TimeDuration::between(t0, TimeStamp::now());
			waitDuration = _sync - realDT;

			if ( waitDuration < TimeDuration::millis(0) )
				break;
		}

		lastDT = TimeDuration::between(t0, TimeStamp::now());
	}
}

} }