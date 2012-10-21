/**
 * @file System.hpp
 *
 * Template for systems.
 */

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "sys/Time.hpp"
#include "sys/SystemActionQueue.hpp"

#include "concurrency/Thread.hpp"
#include "concurrency/Mutex.hpp"
#include "concurrency/Condition.hpp"

#include "profiler/ThreadProfiler.hpp"

#include "Scoped.hpp"
#include "Debug.hpp"

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

private:
	bool _started;
	concurrency::Condition _startupCond;

	const TimeDuration _sync;

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
	 _started(false),
	 _startupCond(),
	 _sync(sync)
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
	_started(system._started),
	_startupCond(), // Conditions can't be moved.
	_sync(system._sync)
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
	static text::string_hash updateName = text::intern("Main loop"); // TODO Get real name for system.
	static const char* TAG = "System";

	Runner runner(_factory());

	Scoped accessScope([&]{ _runnerAccess = &runner; },
	                   [&]{ _runnerAccess = nullptr; });


	{
		concurrency::MutexLockGuard lock(_startupCond.mutex());
		_started = true;
	}
	_startupCond.notifyAll();

	DEBUG_OUT("System", "Started thread main loop");
	for (;;)
	{
		TimeStamp t0 = TimeStamp::now();

		{
			auto profileBlock = profiler::ThreadProfiler::profileBlock(updateName);

			while (!_actions.isEmpty())
				_actions.doAction(runner);

			if (!runner.update())
				return;
		}

		TimeDuration realDT = TimeDuration::between(t0, TimeStamp::now());
		TimeDuration waitDuration = _sync - realDT;

		if (waitDuration.isPositive())
		{
			Thread::sleep(waitDuration);
		}
		else
		{
			VERBOSE_OUT(TAG, "Time budget miss by %ld", realDT - _sync);
			Thread::interruptionPoint();
		}
	}
}

}

#endif
