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

	//template <typename ...Args>
	//System(const TimeDuration &sync, size_t bufferSize, Args&& ...args);

	/**
	 *
	 */
	virtual ~System();

	void waitForStartup();

protected:
	TimeDuration _sync;
	Runner _runner;

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

template<typename Runner>
template<typename T1>
System<Runner>::System(const TimeDuration &sync,
                             size_t bufferSize,
							 T1&& arg1)
		: Thread(),
		  _sync(sync),
		  _runner(std::forward<T1>(arg1)),
		  _actions(bufferSize),
		  _started(false),
		  _startupCond()
{
	//
}

/*template<typename Runner>
template<typename ...Args>
System<Runner>::System(const TimeDuration &sync,
                             size_t bufferSize,
							 Args&& ...args)
		: Thread(),
		  _sync(sync),
		  _runner(std::forward<Args>(args)...),
		  _actions(bufferSize),
		  _started(false),
		  _startupCond()
{
}*/

template<typename Runner>
System<Runner>::~System()
{
	if (getThreadState() != ThreadState::EXITED)
	{
		interrupt();
		join();
	}
}

template<typename Runner>
void System<Runner>::waitForStartup()
{
	_startupCond.waitUntil( [this]() -> bool {return this->_started;} );
}

template<typename Runner>
void System<Runner>::threadMain()
{
	text::String sysName("System"); // TODO Get real name for system.

	text::StringHash sysNameHash = sysName.intern();

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
				_actions.doAction(_runner);

			if (!_runner.update())
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
			// Should warn and add interruption point.
		}
	}
}

}
