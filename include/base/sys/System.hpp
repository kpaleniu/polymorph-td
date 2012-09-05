/**
 * @file System.hpp
 *
 * Interface for systems.
 */

#include "sys/Time.hpp"
#include "sys/Thread.hpp"

#include "profiler/ThreadProfiler.hpp"

namespace sys {

/**
 * Template for systems.
 */
template<typename Runner, typename Data>
class System : public Thread
{
public:
	System(const TimeDuration &sync,
	       Data runnerData)
			: _sync(sync), _runnerData(runnerData)
	{
		//
	}

	virtual ~System()
	{
		//
	}

protected:
	TimeDuration _sync;
	Data _runnerData;

private:
	void threadMain()
	{
		text::String sysName("System");
		text::StringHash sysNameHash = sysName.intern();

		Runner runner(_runnerData);

		while (true)
		{
			TimeStamp t0 = TimeStamp::now();

			{
				profiler::ThreadProfiler::Block frame(sysNameHash);
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
				// Should warn
			}
		}
	}

};

}
