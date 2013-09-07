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



GameRunner::GameRunner(GameRunner::ConstructionArgs&& args,
					   polymorph::sys::NTSystem<GameRunner>& system)
:	_uiSys(args.uiSys),
	_grSys(args.grSys),
	_parentSystem(system),
	_quitting(false),
	_state(std::shared_ptr<BeginState>(new BeginState())),
	_nextState(_state)
{
	setupEventHandlers(_uiSys, _parentSystem);
}

GameRunner::~GameRunner()
{
	if (_state != nullptr)
		_state->exitState(*this);

	removeEventHandlers(_uiSys);
}

bool GameRunner::update(TimeDuration dt)
{
	ASSERT(_nextState, "Next state is null");

	if (_quitting)
		return false;

	if (_state != _nextState)
	{
		_state->exitState(*this);
		_nextState->enterState(*this);
		_state = _nextState;
	}

	_state->update(*this, dt);

	return true;
}

void GameRunner::setState(std::shared_ptr<GameState> nextState)
{
	ASSERT(nextState, "Next state is null");
	_nextState = nextState;
}

void GameRunner::quit()
{
	_quitting = true;
}

}