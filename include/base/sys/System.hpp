/**
 * @file System.hpp
 *
 * Template for systems.
 */

#include "sys/Time.hpp"
#include "sys/Thread.hpp"
#include "sys/Mutex.hpp"
#include "sys/SystemActionQueue.hpp"

#include "profiler/ThreadProfiler.hpp"

#include <iostream>

namespace sys {

/**
 * Template for systems.
 *
 * @param Runner	Type that updates the thread.
 * 					Must implement method update(void) that returns true ifq
 * 					system should continue running.
 * @param Data		Type that is taken as first parameter for type Runner's constructor.
 *
 */
template<typename Runner, typename Data>
class System : public Thread
{
public:
	/**
	 *
	 */
	System(const TimeDuration &sync,
	       Data runnerData,
	       size_t bufferSize);

	/**
	 *
	 */
	virtual ~System();

protected:
	TimeDuration _sync;
	Data _runnerData;
	Runner *_runner;

	SystemActionQueue _actions;

private:
	/**
	 * Calls runner's update method.
	 */
	void threadMain();
};

// Implementation

template<typename Runner, typename Data>
System<Runner, Data>::System(const TimeDuration &sync,
                             Data runnerData,
                             size_t bufferSize)
		: Thread(),
		  _sync(sync),
		  _runnerData(runnerData),
		  _runner(0),
		  _actions(bufferSize)
{
	//
}

template<typename Runner, typename Data>
System<Runner, Data>::~System()
{
	if (getThreadState() != EXITED)
	{
		interrupt();
		join();
	}
}

template<typename Runner, typename Data>
void System<Runner, Data>::threadMain()
{
	text::String sysName("System");
	text::StringHash sysNameHash = sysName.intern();

	Runner runner(_runnerData);

	// Main thread loop.
	for (;;)
	{
		TimeStamp t0 = TimeStamp::now();

		{
			profiler::ThreadProfiler::Block frame(sysNameHash);

			while (!_actions.isEmpty())
				_actions.doAction();

			if (!runner.update())
				return;
		}

		TimeDuration realDT = TimeDuration::between(t0,
		                                            TimeStamp::now());
		TimeDuration waitDuration = _sync
		                            - realDT;

		if (waitDuration.isPositive())
		{
			Thread::sleep(waitDuration);
		}
		else
		{
			// Should warn and add interruption point.
		}
	}
}

}
