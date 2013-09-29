#pragma once

#include "pm_td/GameState.hpp"

#include <NonCopyable.hpp>

namespace polymorph { namespace pm_td {

class GameRunner;

class BeginState : NonCopyable
{
public:
	BeginState(GameRunner& runner);
	BeginState(BeginState&& other);

	void enterState();
	void update(TimeDuration dt);
	void exitState();

private:
	GameRunner& _runner;
};

} }