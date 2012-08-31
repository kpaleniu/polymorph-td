/**
 * This file describes the smallest implemented public API for platform dependent thread class.
 *
 * To include platform specific header, use path "sys/Thread.hpp".
 */

// For compatibility, use same macro-name.
#ifndef THREAD_HPP_
#define THREAD_HPP_

namespace sys {

class Thread
{
public:
	enum ThreadState
	{
		NOT_STARTED = 0, RUNNING, EXITED,
	};

public:
	Thread();
	virtual ~Thread();

	/**
	 * Queues this thread to run.
	 */
	void run();
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

public:
	/**
	 * Suspends thread the specified amount of time.
	 * @param timeDuration time to suspend thread execution.
	 */
	static void sleep(TimeDuration timeDuration);

protected:
	/**
	 * Method to run by this thread.
	 */
	virtual void threadMain() = 0;
};

}

#endif
