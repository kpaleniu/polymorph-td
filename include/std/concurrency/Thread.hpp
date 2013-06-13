/*
 * @file Thread.hpp
 *
 * Contains definition of class Thread as a boost thread wrapper.
 */

#ifndef THREAD_HPP_
#define THREAD_HPP_

#include <Time.hpp>
#include <NonCopyable.hpp>
#include <Exception.hpp>

#include <thread>
#include <condition_variable>

#include <atomic>

namespace polymorph { namespace concurrency {

namespace detail {
	PM_MAKE_EXCEPTION_CLASS(InterruptException, std::exception);
}

class Thread : NonCopyable
{
public:
	typedef std::thread::id ID;

	enum class ThreadState
	{
		NOT_STARTED = 0, RUNNING, EXITED,
	};

public:
	Thread();
	Thread(Thread&& thread);

	virtual ~Thread();

	void start();
	void interrupt();
	void join();

	const ThreadState getThreadState() const;

	const ID getID() const;

	static void sleep(TimeDuration timeDuration);

	static void interruptionPoint();

	static void interruptCurrent();

	static const ID getCurrentID();

protected:
	virtual void threadMain() = 0;

public:

	// STD specific:

	static void setCondition(std::condition_variable* cond);

	static Thread* currentThread(Thread* setter = nullptr);

private:
	std::atomic<ThreadState>				_threadState;
	std::atomic<bool>						_interruptionFlag;
	std::atomic<std::condition_variable*>	_currentCondition;

	std::thread _stdThread;

private:
	static void threadRunner(Thread *thiz);
};

} }

#endif /* THREAD_HPP_ */
