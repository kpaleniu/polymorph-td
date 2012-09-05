/**
 * @file Thread_BOOST.cpp
 *
 * Contains definition of class Thread using boost's thread class.
 */

#include "sys/Thread.hpp"

#include "Debug.hpp"

namespace sys {

Thread::Thread()
		: _threadState(NOT_STARTED), _boostThread()
{

}

Thread::~Thread()
{
	_boostThread.interrupt();
}

void Thread::start()
{
	_boostThread = boost::thread(threadRunner, this);
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

void Thread::sleep(TimeDuration timeDuration)
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
	catch (...)
	{
		// TODO Handle error
	}
}

}
