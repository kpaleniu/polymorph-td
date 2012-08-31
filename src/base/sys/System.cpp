/**
 * @file System.cpp
 *
 *
 */


#include "sys/System.hpp"

namespace sys
{
	System::System(const TimeDuration &sync)
	: _sync(sync)
	{
		//
	}

	System::~System()
	{

	}

	void System::start()
	{
		Thread::run();
	}

	void System::stop()
	{

	}

	void System::pause()
	{

	}

	void System::threadMain()
	{
		while (true)
		{
			TimeStamp t0 = TimeStamp::now();

			update();

			TimeDuration waitDuration = _sync - TimeDuration::between(t0, TimeStamp::now());

			if (waitDuration.isPositive())
			{
				Thread::sleep(waitDuration);
			}
			else
			{
				// Should warn
			}
		}
	}
}

