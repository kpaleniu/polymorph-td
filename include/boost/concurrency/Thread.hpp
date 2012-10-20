/*
 * @file Thread.hpp
 *
 * Contains definition of class Thread as a boost thread wrapper.
 */

#ifndef THREAD_HPP_
#define THREAD_HPP_

#include "sys/time.hpp"
#include "NonCopyable.hpp"

#include <boost/thread.hpp>

namespace concurrency {

class Thread : NonCopyable
{
public:
	typedef boost::thread::id ID;

	enum class ThreadState
	{
		NOT_STARTED = 0, RUNNING, EXITED,
	};

public:
	Thread();
	Thread(Thread&& thread);

	virtual ~Thread();

	/**
	 * Queues this thread to run.
	 */
	void start();
	/**
	 * Requests this thread to quit.
	 */
	void interrupt();
	/**
	 * Blocks the current thread until this thread has finished.
	 */
	void join();

	/**
	 * Gets the state of the thread.
	 * @return current state of thread.
	 */
	const ThreadState getThreadState() const;

	const ID getID() const;

public:
	/**
	 * Suspends thread the specified amount of time.
	 * @param timeDuration time to suspend thread execution.
	 */
	static void sleep(sys::TimeDuration timeDuration);

	static void interruptionPoint();

	static const ID getCurrentID();
protected:
	/**
	 * Method to run by this thread.
	 */
	virtual void threadMain() = 0;

private:
	ThreadState _threadState;

	boost::thread _boostThread;

private:
	static void threadRunner(Thread *thiz);
};

}

#endif /* THREAD_HPP_ */
