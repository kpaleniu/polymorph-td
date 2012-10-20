/**
 * @file UISystem.hpp
 *
 */

#ifndef UISYSTEM_HPP_
#define UISYSTEM_HPP_

#include "NonCopyable.hpp"
#include "stream/ArrayInputStream.hpp"

#include "sys/System.hpp"
#include "sys/Window.hpp"
#include "sys/GraphicsSystem.hpp"

namespace sys {

class UISystemRunner : NonCopyable
{
public:
	UISystemRunner(Window::ConstructionData& winCtorData);
	UISystemRunner(UISystemRunner&& runner);
	~UISystemRunner();

	bool update();

	Window& window();

private:
	Window _window;
	GraphicsSystem _grSys;
};

class UISystem : public System<UISystemRunner>
{
public:
	UISystem(Window::ConstructionData& winCtorData);

	/**
	 * Waits for system start up and returns the window.
	 *
	 * @return	The system's window.
	 */
	Window& waitForWindow();

	// TODO: JUST FOR TESTING
	SystemActionQueue<UISystemRunner>& actionQueue()
	{
		return _actions;
	}
};

}

#endif /* UISYSTEM_HPP_ */
