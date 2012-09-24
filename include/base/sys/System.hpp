/**
 * @file System.hpp
 *
 * Template for systems.
 */

#include "sys/Time.hpp"
#include "sys/SystemActionQueue.hpp"

#include "concurrency/Thread.hpp"
#include "concurrency/Mutex.hpp"
#include "concurrency/Condition.hpp"

#include "profiler/ThreadProfiler.hpp"

#include "Debug.hpp"

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
class System : public concurrency::Thread
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

	void waitForStartup();

protected:
	TimeDuration _sync;
	Data _runnerData;

	SystemActionQueue<action::Action<Runner> > _actions;

private:
	bool _started;
	concurrency::Condition _startupCond;

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
		  _actions(bufferSize),
		  _started(false),
		  _startupCond()
{
	//
}

template<typename Runner, typename Data>
System<Runner, Data>::~System()
{
	if (getThreadState() != ThreadState::EXITED)
	{
		interrupt();
		join();
	}
}

template<typename Runner, typename Data>
void System<Runner, Data>::waitForStartup()
{
	_startupCond.waitUntil( [this]() -> bool {return this->_started;} );
}

template<typename Runner, typename Data>
void System<Runner, Data>::threadMain()
{
	text::String sysName("System"); // TODO Get real name for system.

	text::StringHash sysNameHash = sysName.intern();

	Runner runner(_runnerData);

	{
		concurrency::MutexLockGuard lock(_startupCond.mutex());
		_started = true;
	}
	_startupCond.notifyAll();

	// Main thread loop.
	for (;;)
	{
		TimeStamp t0 = TimeStamp::now();

		{
			profiler::ThreadProfiler::Block frame(sysNameHash);

			while (!_actions.isEmpty())
				_actions.doAction(runner);

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
