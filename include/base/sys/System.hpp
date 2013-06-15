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

	SystemActionQueue<Runner>& actionQueue();

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

} }

#include "sys/System.inl"

#endif
