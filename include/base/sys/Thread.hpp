/*
 * Thread.hpp
 *
 *  Created on: 17 aug 2012
 *      Author: Jens Åkerblom
 */

#ifndef THREAD_HPP_
#define THREAD_HPP_

namespace sys
{
	class Thread
	{
	public:
		enum ThreadState
		{
			NOT_STARTED = 0,
			RUNNING,
			EXITED,
		};

		/**
		 * Platform specific implementation.
		 */
		class PIMPL;

		friend class PIMPL;

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
		 * Returns the state of the thread.
		 */
		const ThreadState getThreadState() const;

	protected:
		/**
		 * Method to run by this thread.
		 */
		virtual void threadMain() = 0;

	private:
		ThreadState _state;

		PIMPL *_pimpl;
	};
}


#endif /* THREAD_HPP_ */
