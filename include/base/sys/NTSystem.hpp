#ifndef NT_SYSTEM_HPP_
#define NT_SYSTEM_HPP_

#include "sys/SystemActionQueue.hpp"
#include "sys/SystemException.hpp"

#include <Time.hpp>
#include <NonCopyable.hpp>

#include <atomic>

namespace polymorph { namespace sys {

/**
 * Non-thread system class.
 */
template <typename Runner>
class NTSystem : NonCopyable
{
public:
	NTSystem(const TimeDuration& sync,
			 std::size_t bufferSize,
			 typename Runner::ConstructionArgs&& args);
	NTSystem(NTSystem&& other);
	virtual ~NTSystem();

	SystemActionQueue<Runner>& actionQueue();

	/**
	 * Makes NTSystem take control over current thread until exited.
	 */
	void enter();

protected:
	// May be invalidated after runner is constructed.
	typename Runner::ConstructionArgs _runnerConstructionArgs;

	SystemActionQueue<Runner> _actions;

	std::atomic<Runner*> _runnerAccess;

	const TimeDuration _sync;

private:
	bool _started;
	concurrency::Condition _startupCond;
};

} }

#include "sys/NTSystem.inl"

#endif