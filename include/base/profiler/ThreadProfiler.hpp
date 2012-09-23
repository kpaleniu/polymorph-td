/**
 * @file SystemProfiler.hpp
 *
 */

#ifndef THREAD_PROFILER_HPP_
#define THREAD_PROFILER_HPP_

#include "text/String.hpp"
#include "concurrency/Thread.hpp"

#include <map>
#include <stack>

namespace profiler {

class ThreadProfiler
{
public:
	class Block
	{
	public:
		Block(text::StringHash blockName);
		~Block();

	private:
		concurrency::Thread::ID _tid;
	};

public:
	friend class Block;

	static ThreadProfiler &profilerFor(concurrency::Thread::ID tid);
	static void dumpAll();
	static void shutdown();

private:
	ThreadProfiler();

	void enterBlock(text::StringHash blockName);
	void exitBlock();



	static std::map<concurrency::Thread::ID,
	        ThreadProfiler *> _threadProfilers;

};

}

#endif /* SYSTEMPROFILER_HPP_ */
