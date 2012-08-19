/**
 * @file Thread.cpp
 *
 * Contains definition of class Thread using boost's thread class.
 */

#include "sys/Thread.hpp"

#include <boost/thread.hpp>

namespace sys
{
	class Thread::PIMPL
	{
	public:
		PIMPL()
		{

		}

		static void threadRunner(Thread *thiz)
		{
			try
			{
				thiz->_state = RUNNING;
				thiz->threadMain();
			}
			catch (...)
			{
				// Do something...
			}

			thiz->_state = EXITED;
		}

		boost::thread _thread;
	};

	Thread::Thread()
			: _pimpl(new PIMPL)
	{

	}

	Thread::~Thread()
	{
		delete _pimpl;
	}

	void Thread::run()
	{
		_pimpl->_thread = boost::thread(PIMPL::threadRunner, this);
	}

	void Thread::join()
	{
		_pimpl->_thread.join();
	}

	void Thread::interrupt()
	{
		_pimpl->_thread.interrupt();
	}

	const Thread::ThreadState Thread::getThreadState() const
	{
		return _state;
	}
}
