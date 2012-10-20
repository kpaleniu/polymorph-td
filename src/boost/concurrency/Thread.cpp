/**
 * @file Thread_BOOST.cpp
 *
 * Contains definition of class Thread using boost's thread class.
 */

#include "concurrency/Thread.hpp"
#include "Exception.hpp"

#include "Debug.hpp"

namespace concurrency {
namespace { const char* TAG = "Thread"; }

Thread::Thread()
:	_threadState(ThreadState::NOT_STARTED),
	_boostThread()
{
}

Thread::Thread(Thread&& thread)
:	_threadState(thread._threadState),
	_boostThread(std::move(thread._boostThread))
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

void Thread::interruptionPoint()
{
	boost::this_thread::interruption_point();
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
	catch (boost::thread_interrupted &/*e*/)
	{
		// Normal exit.
	}
	catch (Exception &e)
	{
		ERROR_OUT(TAG, "Exception caught while running thread\nMessage: %1%", e.what());
	}
	catch (...)
	{
		ERROR_OUT(TAG, "Unknown exception caught while running thread");
	}
}

}
