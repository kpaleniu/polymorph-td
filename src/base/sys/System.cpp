/*
 * System.cpp
 *
 *  Created on: 19 aug 2012
 *      Author: Jens Åkerblom
 */


#include "sys/System.hpp"

namespace sys
{
	System::System(time_t sync)
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

	}
}

