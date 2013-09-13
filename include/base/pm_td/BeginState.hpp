#ifndef PMTD_BEGIN_STATE_HPP_
#define PMTD_BEGIN_STATE_HPP_

#include "pm_td/GameState.hpp"

#include <NonCopyable.hpp>

namespace pm_td {

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

}

#endif