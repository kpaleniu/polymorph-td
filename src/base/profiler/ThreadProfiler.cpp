/**
 * @file ThreadProfiler.cpp
 *
 */

#include "profiler/ThreadProfiler.hpp"

namespace profiler {

std::map<concurrency::Thread::ID, ThreadProfiler *> ThreadProfiler::_threadProfilers;

ThreadProfiler::Block::Block(text::StringHash blockName)
		: _tid(concurrency::Thread::getCurrentID())
{
	ThreadProfiler::profilerFor(_tid).enterBlock(blockName);
}

ThreadProfiler::Block::~Block()
{
	ThreadProfiler::profilerFor(_tid).exitBlock();
}

// ThreadProfiler definition.

ThreadProfiler::ThreadProfiler()
{

}

void ThreadProfiler::enterBlock(text::StringHash blockName)
{
	// TODO
}

void ThreadProfiler::exitBlock()
{
	// TODO
}

ThreadProfiler &ThreadProfiler::profilerFor(concurrency::Thread::ID tid)
{
	ThreadProfiler *rProfiler;

	if (_threadProfilers.count(tid) == 0)
	{
		rProfiler = new ThreadProfiler();
		_threadProfilers[tid] = rProfiler;
	}
	else
		rProfiler = _threadProfilers[tid];

	return *rProfiler;
}

void ThreadProfiler::dumpAll()
{
	// TODO
}

void ThreadProfiler::shutdown()
{
	// TODO
}

}
