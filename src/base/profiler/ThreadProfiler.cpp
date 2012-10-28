/**
 * @file ThreadProfiler.cpp
 *
 */

#include "profiler/ThreadProfiler.hpp"

#include "Assert.hpp"

#include <algorithm>

using namespace concurrency;
using namespace std;

namespace profiler {

std::map<Thread::ID, ThreadProfiler*> ThreadProfiler::_threadProfilers;

ThreadProfiler::ThreadProfiler()
: _blocks()
{
}

void ThreadProfiler::enterBlock(text::string_hash blockName)
{
	_blocks[blockName].atEnter = sys::TimeStamp::now();
}

void ThreadProfiler::exitBlock(text::string_hash blockName)
{
	using namespace sys;

	BlockInfo& block = _blocks[blockName];
	TimeDuration blockDuration = TimeDuration::between(block.atEnter, TimeStamp::now());

	++block.count;

	if (blockDuration > block.longest)
	{
		block.longest = blockDuration;
	}

	if (blockDuration > TimeDuration::millis(0) &&
				(blockDuration < block.shortest ||
				 block.shortest.isNegative()) )
	{
		block.shortest = blockDuration;
	}

}

ThreadProfiler& ThreadProfiler::profilerFor(Thread::ID tid)
{
	ThreadProfiler* rProfiler;

	if (_threadProfilers.count(tid) == 0)
	{
		rProfiler = new ThreadProfiler();
		_threadProfilers[tid] = rProfiler;
	}
	else
		rProfiler = _threadProfilers[tid];

	return *rProfiler;
}

void ThreadProfiler::dumpAll(ostream& out)
{
	out << "---Thread profiler---" << endl;
	for_each(_threadProfilers.begin(),
	         _threadProfilers.end(),
			[&](pair<Thread::ID, ThreadProfiler*> profiler)
			{
				out << "---Profiler " << profiler.first << endl;
				for_each(profiler.second->_blocks.begin(),
				         profiler.second->_blocks.end(),
				        [&](pair<text::string_hash, BlockInfo> block)
				        {
							out << "\tBlock \"" << text::get(block.first) << "\"" << endl;
							out << "\t\tCount    " << block.second.count << endl;
							out << "\t\tShortest " << block.second.shortest << endl;
							out << "\t\tLongest  " << block.second.longest << endl << endl;
				        });
				out << endl;
			});
}

void ThreadProfiler::shutdown()
{
	for_each(_threadProfilers.begin(),
	         _threadProfilers.end(),
	         [=](pair<Thread::ID, ThreadProfiler*> profiler) { delete profiler.second; });
	_threadProfilers.clear();
}

ProfileBlock ThreadProfiler::profileBlock(text::string_hash blockID)
{
	Thread::ID tid = Thread::getCurrentID();
	return ProfileBlock([=] { ThreadProfiler::profilerFor(tid).enterBlock(blockID); },
	                    [=] { ThreadProfiler::profilerFor(tid).exitBlock(blockID); });
}

}
