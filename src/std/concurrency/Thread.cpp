
#include "concurrency/Thread.hpp"

#include <Cpp11.hpp>
#include <Debug.hpp>
#include <Assert.hpp>

namespace polymorph { namespace concurrency {

namespace { 

const char* TAG = "Thread"; 

}



Thread::Thread()
:	_threadState(ThreadState::NOT_STARTED),
	_stdThread(),
	_interruptionFlag(false),
	_currentCondition(nullptr)
{
}

Thread::Thread(Thread&& thread)
:	_threadState(thread._threadState.load()),
	_stdThread(std::move(thread._stdThread))
{
}

Thread::~Thread()
{
	_interruptionFlag = true;

	if (_stdThread.joinable()) // Will return false if start has not been called.
	{
		interrupt();
		_stdThread.join();
	}
}

void Thread::start()
{
	_stdThread = std::thread(threadRunner, this);
}

void Thread::join()
{
	interruptionPoint();

	if (_stdThread.joinable())
		_stdThread.join();
}

void Thread::interrupt()
{
	std::condition_variable* condition = _currentCondition.load();
	_interruptionFlag = true;

	if (condition != nullptr)
		condition->notify_all();
}

const Thread::ThreadState Thread::getThreadState() const
{
	return _threadState;
}

const Thread::ID Thread::getID() const
{
	return _stdThread.get_id();
}

void Thread::sleep(TimeDuration timeDuration)
{
	// Let non-pm threads sleep as well.
	if (currentThread() != nullptr)
		interruptionPoint();

	std::this_thread::sleep_for(timeDuration._std__timeDuration);
}

void Thread::interruptionPoint()
{
	Thread* thisThread = currentThread();

	if (thisThread == nullptr)
		return;

	bool interrupted = thisThread->_interruptionFlag;

	if (interrupted)
		interruptCurrent();
}

void Thread::interruptCurrent()
{
	Thread* thisThread = currentThread();
	if (thisThread != nullptr)
		thisThread->_interruptionFlag = false;

	throw InterruptException();
}

const Thread::ID Thread::getCurrentID()
{
	return std::this_thread::get_id();
}

void Thread::threadRunner(Thread *thiz)
{
    ASSERT(thiz, "Thread pointer is null");
    
	currentThread(thiz);

	VERBOSE_OUT(TAG, "Thread starting");

	try
	{
		thiz->_threadState = ThreadState::RUNNING;
		thiz->threadMain();
	}
	catch (InterruptException&)
	{
		// Normal exit.
	}
	catch (Exception &e)
	{
		ERROR_OUT(TAG, "Exception caught while running thread\nMessage: %s", e.what());
	}
	catch (...)
	{
		ERROR_OUT(TAG, "Unknown exception caught while running thread");
	}

	thiz->_threadState = ThreadState::EXITED;
	VERBOSE_OUT(TAG, "Thread exited");
}

void Thread::setCondition(std::condition_variable* cond)
{
	Thread* thisThread = currentThread();

	if (thisThread != nullptr)
		thisThread->_currentCondition = cond;
}

Thread* Thread::currentThread(Thread* setter)
{
#if defined(NO_THREAD_LOCAL)
#   if defined(_MSC_VER)
        __declspec( thread ) static Thread* thisThread = nullptr;
#   elif defined(__APPLE__) || ( __GNUC__ <= 4 && __GNUC_MINOR__ < 8 )
        static __thread Thread* thisThread = nullptr;
#   endif
#else
	thread_local static Thread* thisThread = nullptr;
#endif

	if (setter != nullptr)
	{
		ASSERT(thisThread == nullptr, "Trying to overwrite current thread.");
		thisThread = setter;
	}

	return thisThread;
}

} }
