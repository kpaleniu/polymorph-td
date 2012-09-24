/*
 * @file Thread.hpp
 *
 * Contains mockup interface for class Thread.
 */

#ifndef THREAD_HPP_
#define THREAD_HPP_

#include "sys/Time.hpp"

/**
 *  Platform specific type.
 */
typedef void *unknown_t;

namespace concurrency {

/**
 * Platform specific thread class.
 * This mockup class specifies the public and protected
 * interface for class Thread.
 */
class Thread
{
public:
	// Member types:

	/**
	 * ID of thread.
	 * Must overload operators == != and be able to
	 * be stored as keys in std associative collections.
	 */
	typedef unknown_t ID;

	/**
	 * State of thread.
	 */
	enum class ThreadState
	{
		NOT_STARTED = 0, RUNNING, EXITED,
	};

public:
	/**
	 * Parameter-less constructor.
	 */
	Thread();
	/**
	 * Virtual destructor.
	 */
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
	 * Should trigger assertion if trying to join self.
	 */
	void join();

	/**
	 * Gets the state of the thread.
	 * @return current state of thread.
	 */
	const ThreadState getThreadState() const;

	/**
	 * @returns The id of this thread.
	 */
	const ID getID() const;

public:
	/**
	 * Suspends thread the specified amount of time.
	 * @param timeDuration time to suspend thread execution.
	 */
	static void sleep(sys::TimeDuration timeDuration);
	/**
	 * @returns the id of the thread calling this method.
	 */
	static const ID getCurrentID();

protected:
	/**
	 * Method to run by this thread.
	 */
	virtual void threadMain() = 0;
};

// Mockup implementation

Thread::Thread()
{
}

Thread::~Thread()
{
}

void Thread::start()
{
}

void Thread::interrupt()
{
}

void Thread::join()
{
}

const Thread::ThreadState Thread::getThreadState() const
{
	return ThreadState::NOT_STARTED;
}

const Thread::ID Thread::getID() const
{
	return ID(0);
}

void Thread::sleep(sys::TimeDuration timeDuration)
{
}

const Thread::ID Thread::getCurrentID()
{
	return ID(0);
}

}

#endif /* THREAD_HPP_ */
