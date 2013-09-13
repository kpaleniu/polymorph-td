#include "pm_td/GameRunner.hpp"

#include "pm_td/BeginState.hpp"

#include <text/util.hpp>
#include <Assert.hpp>

namespace pm_td {

namespace runner_action_id
{
	event_action_id QUIT = text::hash("GamerRunner_QUIT");
}



void setupEventHandlers(polymorph::sys::UISystem& uiSys,
						polymorph::sys::NTSystem<GameRunner>& system)
{
	uiSys.addEventAction<polymorph::sys::event::Quit>
	(
		runner_action_id::QUIT,
		[&system]
		{
			system.actionQueue().pushAction
			(
				[](GameRunner& runner) 
				{ 
					runner.quit(); 
				}
			);
		}
	);
}

void removeEventHandlers(polymorph::sys::UISystem& uiSys)
{
	uiSys.removeEventAction<polymorph::sys::event::Quit>(runner_action_id::QUIT);
}


GameRunner::ConstructionArgs::ConstructionArgs(polymorph::sys::UISystem& uiSys_,
											   polymorph::sys::GraphicsSystem& grSys_)
:	uiSys(uiSys_), grSys(grSys_)
{
}

GameRunner::ConstructionArgs::ConstructionArgs(ConstructionArgs&& other)
:	uiSys(other.uiSys), grSys(other.grSys)
{
}

GameRunner::GameRunner(GameRunner::ConstructionArgs&& args,
					   polymorph::sys::NTSystem<GameRunner>& system)
:	_uiSys(args.uiSys),
	_grSys(args.grSys),
	_parentSystem(system),
	_quitting(false),
	_state(BeginState(*this)),
	_nextState()
{
	setupEventHandlers(_uiSys, _parentSystem);
}

GameRunner::~GameRunner()
{
	if (_state)
		_state.exitState();

	removeEventHandlers(_uiSys);
}

bool GameRunner::update(TimeDuration dt)
{
	if (_quitting)
		return false;

	if (_nextState)
	{
		_state.exitState();
		_nextState.enterState();
		_state = std::move(_nextState);
	}

	_state.update(dt);

	return true;
}

void GameRunner::setState(GameState&& nextState)
{
	ASSERT(nextState, "Next state is nothing");
	_nextState = std::move(nextState);
}

void GameRunner::quit()
{
	_quitting = true;
}

}