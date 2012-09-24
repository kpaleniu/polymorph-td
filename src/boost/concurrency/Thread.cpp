/**
 * @file Thread_BOOST.cpp
 *
 * Contains definition of class Thread using boost's thread class.
 */

#include "concurrency/Thread.hpp"
#include "Exception.hpp"

#include "Debug.hpp"

namespace concurrency {

Thread::Thread()
		: _threadState(ThreadState::NOT_STARTED),
		  _boostThread()
{

}

Thread::~Thread()
{
	_boostThread.interrupt();
}

void Thread::start()
{
	_boostThread = boost::thread(threadRunner,
	                             this);
}

void Thread::join()
{
	_boostThread.join();
}

void Thread::interrupt()
{
	_boostThread.interrupt();
}

const Thread::ThreadState Thread::getThreadState() const
{
	return _threadState;
}

const Thread::ID Thread::getID() const
{
	return _boostThread.get_id();
}

void Thread::sleep(sys::TimeDuration timeDuration)
{
	boost::this_thread::sleep(timeDuration.timeDuration);
}

const Thread::ID Thread::getCurrentID()
{
	return boost::this_thread::get_id();
}

void Thread::threadRunner(Thread *thiz)
{
	try
	{
		thiz->threadMain();
	}
	catch (boost::thread_interrupted &e)
	{
		// Normal exit.
	}
	catch (Exception &e)
	{
		DEBUG_OUT_UNIT(THREAD_UNIT,
		               "Exception caught in thread " << boost::this_thread::get_id());
		DEBUG_OUT_UNIT(THREAD_UNIT,
		               "Message: " << e.what());

	}
	catch (...)
	{
		DEBUG_OUT_UNIT(THREAD_UNIT,
		               "Unknown exception caught in thread " << boost::this_thread::get_id());
	}
}

}
