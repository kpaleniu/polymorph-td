/**
 * @file ThreadProfiler.hpp
 *
 * Contains interface for class ThreadProfiler.
 */

#ifndef THREAD_PROFILER_HPP_
#define THREAD_PROFILER_HPP_

#include "concurrency/Thread.hpp"
#include "sys/Time.hpp"
#include "text/util.hpp"
#include "Scoped.hpp"

#include <map>
#include <stack>
#include <ostream>

namespace profiler {

typedef Scoped ProfileBlock;

class ThreadProfiler
{
public:
	static void dumpAll(std::ostream& out);
	static void shutdown();

	static ProfileBlock profileBlock(text::string_hash blockID);

private:
	ThreadProfiler();

	void enterBlock(text::string_hash blockName);
	void exitBlock(text::string_hash blockName);

	static ThreadProfiler& profilerFor(concurrency::Thread::ID tid);

private:
	struct BlockInfo
	{
		BlockInfo()
		: longest( sys::TimeDuration::millis(0) ),
		  shortest( sys::TimeDuration::millis(-1) ),
		  count(0),
		  atEnter( sys::TimeStamp::now() )
		{}

		sys::TimeDuration longest;
		sys::TimeDuration shortest;

		unsigned long count;

		// Buffer
		sys::TimeStamp atEnter;
	};

	std::map<text::string_hash, BlockInfo> _blocks;

	static std::map<concurrency::Thread::ID,
	        ThreadProfiler*> _threadProfilers;

};

}

#endif /* SYSTEMPROFILER_HPP_ */
