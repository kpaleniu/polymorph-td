/**
 * @file Scoped.hpp
 *
 */

#ifndef SCOPED_HPP_
#define SCOPED_HPP_

#include "NonCopyable.hpp"
#include <functional>


/**
 * A helper class which can be used to invoke
 * desired functionality on scope exit.
 */
class Scoped : NonCopyable
{
public:

	/**
	 * @param entry Callable object that is invoked upon object construction.
	 * @param exit Callable object that is invoked upon object destruction.
	 */
	template <typename Entry, typename Exit>
	Scoped(Entry entry, Exit exit) : _atExit(exit)
	{
		entry();
	}

	Scoped(Scoped&& scoped)
	{
		// ensure that scoped._atExit holds an invalid target
		std::swap(_atExit, scoped._atExit);
	}

	~Scoped()
	{
		if (_atExit) _atExit();
	}

private:
	std::function<void ()> _atExit;
};

#endif // SCOPED_HPP_
