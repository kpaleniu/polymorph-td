/**
 * @file System.hpp
 *
 * Template for systems.
 */

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "sys/SystemActionQueue.hpp"

#include <concurrency/Thread.hpp>
#include <concurrency/Mutex.hpp>
#include <concurrency/Condition.hpp>

#include <profiler/ThreadProfiler.hpp>

#include <Time.hpp>
#include <Scoped.hpp>
#include <Debug.hpp>

#include <functional>
#include <atomic>

namespace sys {

/**
 * Template for systems.
 *
 * @param Runner	Type that updates the thread.
 * 					Runner must be move constructable and it must implement
 * 					method update(void) that returns true if system should
 * 					continue running.
 *
 * 					FIX Current implementation crashes if runner is accessed
 * 					after it's been destroyed.
 *
 */
template<typename Runner>
class System : public concurrency::Thread
{
public:

	/**
	 *
	 */
	template <typename T1>
	System(const TimeDuration &sync, size_t bufferSize, T1&& arg1);

	System(System&& system);

	/** 
	 * NOTE: due to a defect in the C++ standard(!!) implementing this function is not
	 * possible by simply using lambda '[&] { return Runner(std::forward<Args>(args)...); }'
	 * to construct the _factory member.
	 * http://www.open-std.org/jtc1/sc22/wg21/docs/cwg_defects.html#904
	 */
	//template <typename ... Args>
	//System(const TimeDuration &sync, size_t bufferSize, Args&& args);

	/**
	 *
	 */
	virtual ~System();

	void waitForStartup();

protected:
	std::function<Runner ()> _factory;

	SystemActionQueue<Runner> _actions;


	std::atomic<Runner*> _runnerAccess;

	const TimeDuration _sync;

private:
	bool _started;
	concurrency::Condition _startupCond;

	/**
	 * Calls runner's update method.
	 */
	void threadMain();
};

// Implementation

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
void System<Runner>::threadMain()
{
	// Strings for profiler.
	static text::string_hash updateName =
			text::intern(std::string(Runner::getSystemName()) + ": update");

	static text::string_hash actionName =
			text::intern(std::string(Runner::getSystemName()) + ": action");
	//

	static const char* TAG = "System";

	Runner runner(_factory());

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
			auto profileBlock = profiler::ThreadProfiler::profileBlock(updateName);

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
				auto profileBlock = profiler::ThreadProfiler::profileBlock(actionName);
				_actions.doAction(runner);
			}

			realDT = TimeDuration::between(t0, TimeStamp::now());
			waitDuration = _sync - realDT;

			if ( !waitDuration.isPositive() )
				break;
		}
	}
}

}

#endif
