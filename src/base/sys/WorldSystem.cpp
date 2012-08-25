/**
 * @file WorldSystem.cpp
 *
 */

#include "sys/WorldSystem.hpp"

namespace sys {

WorldSystem::WorldSystem(gr::Window::ConstructionData &winData)
		: System(time_t(60)), _window(winData)
{

}

WorldSystem::~WorldSystem()
{

}

void WorldSystem::update()
{

}

}

