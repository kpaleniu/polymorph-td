#pragma once

#include "pm_td/GameState.hpp"

namespace polymorph { namespace pm_td {

class GameRunner;

class MainMenuState : NonCopyable
{
public:
	MainMenuState(GameRunner& runner);
	MainMenuState(MainMenuState&& other);

	void enterState();
	void exitState();
	void update(TimeDuration dt);

private:
	GameRunner& _runner;
};


} }