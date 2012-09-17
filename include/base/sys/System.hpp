/**
 * @file System.hpp
 *
 * Interface for systems.
 */

#include "sys/Time.hpp"
#include "sys/Thread.hpp"
#include "sys/Mutex.hpp"

#include "profiler/ThreadProfiler.hpp"

#include <iostream>

namespace sys {

/**
 * Template for systems.
 */
template<typename Runner, typename Data>
class System : public Thread
{
public:
	/**
	 *
	 */
	System(const TimeDuration &sync,
	       Data runnerData);

	/**
	 *
	 */
	virtual ~System();

	//std::ostream &toRunner();

protected:
	TimeDuration _sync;
	Data _runnerData;
	Runner *_runner;

	//std::iostream &_toRunner;
	//std::iostream &_toRunnerCache;

	Mutex _writerMutex;

private:
	/**
	 * Calls runner's update method.
	 */
	void threadMain();
};

// Implementation

template<typename Runner, typename Data>
System<Runner, Data>::System(const TimeDuration &sync,
                             Data runnerData)
		: Thread(),
		  _sync(sync),
		  _runnerData(runnerData)
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

			MutexLockGuard lock(_writerMutex);

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
