#include "pm_td/GameRunner.hpp"

#include "pm_td/BeginState.hpp"

#include <sys/Systems.hpp>

#include <Assert.hpp>
#include <Hasher.hpp>

#include <string>

namespace polymorph { namespace pm_td {

namespace runner_action_id
{
	event_action_id QUIT = hash("GamerRunner_QUIT");
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

GameRunner::GameRunner(GameRunner::ConstructionArgs&&,
					   polymorph::sys::NTSystem<GameRunner>& system)
:	_parentSystem(system),
	_quitting(false),
	_gameScene(sys::Systems::system<sys::GraphicsSystem>().meshes()),
	_state(BeginState(*this)),
	_nextState()
{
	setupEventHandlers(polymorph::sys::Systems::system<polymorph::sys::UISystem>(), 
					   _parentSystem);
}

GameRunner::~GameRunner()
{
	if (_state)
		_state.exitState();

	removeEventHandlers(polymorph::sys::Systems::system<polymorph::sys::UISystem>());
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

	_gameScene.flush();

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

} }