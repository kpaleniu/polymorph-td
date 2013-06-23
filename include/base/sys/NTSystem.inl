#include "sys/NTSystem.hpp"

#include <concurrency/Thread.hpp>

namespace polymorph { namespace sys {

template <typename Runner>
NTSystem<Runner>::NTSystem(const TimeDuration& sync,
						   std::size_t bufferSize,
						   typename Runner::ConstructionArgs&& runnerConstructionArgs)
:	_runnerConstructionArgs(std::move(runnerConstructionArgs)),
	_actions(bufferSize),
	_runnerAccess(nullptr),
	_sync(sync),
	_started(false),
	_startupCond()
{
}

template <typename Runner>
NTSystem<Runner>::NTSystem(NTSystem&& other)
:	_runnerConstructionArgs(std::move(other._runnerConstructionArgs)),
	_actions(std::move(other._actions)),
	_runnerAccess(other._runnerAccess.load()),
	_sync(other._sync),
	_started(other._started),
	_startupCond()
{
}

template <typename Runner>
NTSystem<Runner>::~NTSystem()
{
}

template <typename Runner>
SystemActionQueue<Runner>& NTSystem<Runner>::actionQueue()
{
	return _actions;
}

template <typename Runner>
void NTSystem<Runner>::enter()
{
	// Strings for profiler.
	/*
	text::string_hash updateName =
			text::intern(std::string(Runner::getSystemName()) + ": update");

	text::string_hash actionName =
			text::intern(std::string(Runner::getSystemName()) + ": action");
	*/
	//

	static const char* TAG = "System";

	try
	{
		Runner runner( std::move(_runnerConstructionArgs), *this );

		Scoped accessScope([&]{ _runnerAccess = &runner; },
						   [&]{ _runnerAccess = nullptr; });


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
	catch (polymorph::concurrency::InterruptException&)
	{
		// Normal exit
	}
}


	
} }