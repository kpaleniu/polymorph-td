/**
 * @file WorldSystem.cpp
 *
 */

#include "sys/WorldSystem.hpp"

#include "gr/Surface.hpp"

#include "Debug.hpp"

namespace sys {

WorldSystemRunner::WorldSystemRunner(sys::Window::ConstructionData &winData)
		: _window(winData),
		  _renderer(_window.surface())
{

}

bool WorldSystemRunner::update()
{
	DEBUG_OUT("WorldSystem updateSystem");

	_renderer.clearBuffers();
	_window.surface().flipBuffers();
	_window.handleEvents();

	return true;
}

}

