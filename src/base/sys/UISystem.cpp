/**
 * @file UISystem.cpp
 *
 */

#include "sys/UISystem.hpp"

#include <input/WindowInputSource.hpp>

#include <Time.hpp>
#include <Assert.hpp>
#include <Debug.hpp>
#include <BuildConfig.hpp>


namespace sys {

// print tag
namespace { const char* TAG_RUNNER = "UISystemRunner";
			const char* TAG_SYSTEM = "UISystem"; }

UISystemRunner::UISystemRunner(Window::ConstructionData& winCtorData)
:	_window(winCtorData),
	_grSys(_window),
 	_eventAdapter()
{
	DEBUG_OUT(TAG_RUNNER, "Constructed");

	_window.show(true);
	_window.inputSource().setKeyListener(&_eventAdapter);
	_window.inputSource().setPointerListener(&_eventAdapter);
	_window.inputSource().setSurfaceListener(&_eventAdapter);

	_grSys.start();

	_grSys.waitForStartup();
}

UISystemRunner::UISystemRunner(UISystemRunner&& runner)
:	_window(std::move(runner._window)),
 	_grSys(std::move(runner._grSys)),
	_eventAdapter(runner._eventAdapter) // TODO Implement move.
{
	VERBOSE_OUT(TAG_RUNNER, "Moved");

	_window.inputSource().setKeyListener(&_eventAdapter);
	_window.inputSource().setPointerListener(&_eventAdapter);
	_window.inputSource().setSurfaceListener(&_eventAdapter);
}

UISystemRunner::~UISystemRunner()
{
	_grSys.interrupt();
	_grSys.join();

	DEBUG_OUT(TAG_RUNNER, "Destroyed");
}

bool UISystemRunner::update()
{
	TimeStamp start = TimeStamp::now();

	while (_window.inputSource().handleInput())
	{
		if (TimeDuration::between(start, TimeStamp::now())
			> TimeDuration::millis(settings::sys::uiSystemSyncMillis))
			break;
	}

	return true;
}

Window& UISystemRunner::window()
{
	return _window;
}

event::UIEventManager& UISystemRunner::uiEvents()
{
	return _eventAdapter.eventManager;
}

GraphicsSystem& UISystemRunner::graphics()
{
	return _grSys;
}


UISystem::UISystem(Window::ConstructionData& winCtorData)
:	System(TimeDuration::millis(settings::sys::uiSystemSyncMillis),
 	       256,
 	       winCtorData),
 	_states()
{
	pushState(StateDesc{event::UIEventManager()});

	DEBUG_OUT(TAG_SYSTEM, "Constructed");
}

Window& UISystem::waitForWindow()
{
	waitForStartup();

	UISystemRunner* runner = _runnerAccess.load();
	ASSERT(runner != nullptr, "Runner has started but cannot be accessed, is the system dying?");

	return runner->window();
}

GraphicsSystem& UISystem::waitForGraphicsSystem()
{
	waitForStartup();

	UISystemRunner* runner = _runnerAccess.load();
	ASSERT(runner != nullptr, "Runner isn't alive");

	return runner->graphics();
}

void UISystem::pushState(const StateDesc& newState)
{
	_states.push(newState);
	setState(_states.top());
}

void UISystem::popState()
{
	ASSERT(_states.size() > 1, "Stack underflow"); // _state[0] is "null state".

	_states.pop();
	setState(_states.top());
}

void UISystem::setState(const StateDesc& state)
{
	// Must be captured by value to avoid corruption due to concurrency.
	_actions.pushAction([=](UISystemRunner& runner)
    {
		runner.uiEvents() = state.eventManager;
    });
}

}



