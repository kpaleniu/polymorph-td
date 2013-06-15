#include "sys/System.hpp"


namespace polymorph { namespace sys {

template<typename Runner>
template<typename T1>
System<Runner>::System(const TimeDuration &sync,
                             size_t bufferSize,
							 T1&& arg1)
:	Thread(),
	_factory(),
	_actions(bufferSize),
	_runnerAccess(nullptr),
	_sync(sync),
	_started(false),
	_startupCond()
{
	// NOTE: due to a limitation in the VC++11's implementation of
	// lambdas the template parameter is not visible inside the lambda
	// if used inside the initializer list ...
	_factory = [&] { return Runner(std::forward<T1>(arg1)); };
}

template<typename Runner>
System<Runner>::System(System&& system)
:	Thread(std::move(system)),
	_factory(system._factory),
	_actions(std::move(system._actions)),
	_runnerAccess(system._runnerAccess.load()),
	_sync(system._sync),
	_started(system._started),
	_startupCond() // Conditions can't be moved.
{
	system._runnerAccess = nullptr;
}

template<typename Runner>
System<Runner>::~System()
{
}

template<typename Runner>
void System<Runner>::waitForStartup()
{
	_startupCond.waitUntil( [this]() -> bool {return this->_started;} );
}

template<typename Runner>
SystemActionQueue<Runner>& System<Runner>::actionQueue()
{
	if (getThreadState() == ThreadState::EXITED)
		throw SystemDeadException();

	return _actions;
}

template<typename Runner>
void System<Runner>::threadMain()
{
	// Strings for profiler.
	text::string_hash updateName =
			text::intern(std::string(Runner::getSystemName()) + ": update");

	text::string_hash actionName =
			text::intern(std::string(Runner::getSystemName()) + ": action");
	//

	static const char* TAG = "System";

	Runner runner(_factory());

	Scoped accessScope([&]{ DEBUG_OUT(TAG, "Runner set %p", &runner); _runnerAccess = &runner; },
	                   [&]{ DEBUG_OUT(TAG, "Runner unset %p", &runner); _runnerAccess = nullptr; });


	{
		concurrency::MutexLockGuard lock(_startupCond.mutex());
		_started = true;
	}
	_startupCond.notifyAll();

	//---------------- Main system loop ----------------//

	DEBUG_OUT(TAG, "Started thread main loop");
	for (;;)
	{
		TimeStamp t0 = TimeStamp::now();

		//---------------- Runner updating ----------------//

		{
			// auto profileBlock = profiler::ThreadProfiler::profileBlock(updateName);

			if (!runner.update())
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
	}
}

} }