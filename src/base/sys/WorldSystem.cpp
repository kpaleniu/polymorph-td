/**
 * @file WorldSystem.cpp
 *
 */

#include "sys/WorldSystem.hpp"

#include "gr/Surface.hpp"

#include "Debug.hpp"

namespace sys {

WorldSystem::WorldSystem(sys::Window::ConstructionData &winData)
		: System(TimeDuration::millis(33)), _window(winData), _renderer(_window.surface())
{

}

WorldSystem::~WorldSystem()
{

}

void WorldSystem::update()
{
	DEBUG_OUT("WorldSystem update");
}

}

