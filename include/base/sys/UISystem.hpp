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

#include <Event.hpp>
#include <NonCopyable.hpp>
#include <Assert.hpp>

#include <stack>

namespace polymorph { namespace sys {

class UISystemRunner : NonCopyable
{
public:
	typedef Window::ConstructionData ConstructionArgs;

	UISystemRunner(Window::ConstructionData&& winCtorData, System<UISystemRunner>&);
	UISystemRunner(UISystemRunner&& runner);
	~UISystemRunner();

	bool update(TimeDuration dt);

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
	UISystem(Window::ConstructionData&& winCtorData);

	/**
	 * Waits for system start up and returns the window.
	 *
	 * @return	The system's window.
	 */
	Window& waitForWindow();

	GraphicsSystem& waitForGraphicsSystem();


	// Event helpers

	template <typename Event>
	void addEventAction(event_action_id id, const typename EventManager<Event>::ActionType& action);

	template <typename Event>
	void removeEventAction(event_action_id id);

	//
};

} }

#include "sys/UISystem.inl"

#endif /* UISYSTEM_HPP_ */
