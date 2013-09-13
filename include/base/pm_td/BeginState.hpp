#ifndef PMTD_BEGIN_STATE_HPP_
#define PMTD_BEGIN_STATE_HPP_

#include "pm_td/GameState.hpp"

namespace pm_td {

class GameRunner;

class BeginState
{
public:
	BeginState(GameRunner& runner);

	void enterState();
	void update(TimeDuration dt);
	void exitState();

private:
	GameRunner& _runner;
};

}

#endif