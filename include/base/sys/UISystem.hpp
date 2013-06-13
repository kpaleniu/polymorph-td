/**
 * @file UISystem.hpp
 *
 */

#ifndef UISYSTEM_HPP_
#define UISYSTEM_HPP_


#include "sys/System.hpp"
#include "sys/Window.hpp"
#include "sys/GraphicsSystem.hpp"
#include "sys/UIEvents.hpp"

#include <NonCopyable.hpp>
#include <Assert.hpp>

#include <stack>

namespace polymorph { namespace sys {

class UISystemRunner : NonCopyable
{
public:
	UISystemRunner(Window::ConstructionData& winCtorData);
	UISystemRunner(UISystemRunner&& runner);
	~UISystemRunner();

	bool update();

	Window& window();
	GraphicsSystem& graphics();
	event::UIEventManager& uiEvents();

	static const char* getSystemName()
	{ return "UISystem"; }

private:
	Window _window;
	GraphicsSystem _grSys;

	event::UIEventAdapter _eventAdapter;
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

	GraphicsSystem& waitForGraphicsSystem();
};

} }

#endif /* UISYSTEM_HPP_ */
