/**
 * @file System.hpp
 *
 * Template for systems.
 */

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "sys/SystemActionQueue.hpp"
#include "sys/SystemException.hpp"

#include <concurrency/Thread.hpp>
#include <concurrency/Mutex.hpp>
#include <concurrency/Condition.hpp>

// #include <profiler/ThreadProfiler.hpp>

#include <Time.hpp>
#include <Scoped.hpp>
#include <Debug.hpp>

#include <functional>
#include <atomic>

namespace polymorph { namespace sys {

PM_MAKE_EXCEPTION_CLASS(SystemDeadException, SystemException);


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

	System(const TimeDuration& sync, 
		   size_t bufferSize, 
		   typename Runner::ConstructionArgs&& args);
	System(System&& system);
	virtual ~System();

	void waitForStartup();

	SystemActionQueue<Runner>& actionQueue();

protected:
	// May be invalidated after runner is constructed.
	typename Runner::ConstructionArgs _runnerConstructionArgs;

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

} }

#include "sys/System.inl"

#endif
