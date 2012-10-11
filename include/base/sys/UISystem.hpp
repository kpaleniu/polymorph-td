/**
 * @file UISystem.hpp
 *
 */

#ifndef UISYSTEM_HPP_
#define UISYSTEM_HPP_

#include "NonCopyable.hpp"
#include "action/Action.hpp"
#include "stream/ArrayInputStream.hpp"
#include "sys/System.hpp"
#include "sys/Window.hpp"

namespace sys {

class UISystemRunner : NonCopyable
{
public:
	UISystemRunner(Window::ConstructionData& winCtorData);
	UISystemRunner(UISystemRunner&& runner);

	bool update();

	Window& window();

private:
	Window _window;
};

class UISystem : public System<UISystemRunner>
{
public:
	UISystem(Window::ConstructionData& winCtorData, const TimeDuration& sync);

	/**
	 * Waits for system start up and returns the window.
	 *
	 * @return	The system's window.
	 */
	Window& waitForWindow();

};

}

#endif /* UISYSTEM_HPP_ */
