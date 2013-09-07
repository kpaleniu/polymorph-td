#ifndef PMTD_GAMERUNNER_HPP_
#define PMTD_GAMERUNNER_HPP_

#include "pm_td/GameState.hpp"

#include <sys/NTSystem.hpp>
#include <sys/UISystem.hpp>
#include <sys/GraphicsSystem.hpp>

#include <memory>

namespace pm_td {

class GameRunner
{
public:
	struct ConstructionArgs
	{
		polymorph::sys::UISystem&		uiSys;
		polymorph::sys::GraphicsSystem& grSys;
	};


	GameRunner(ConstructionArgs&& args,
			   polymorph::sys::NTSystem<GameRunner>& system);

	~GameRunner();

	bool update(TimeDuration dt);

	void setState(std::shared_ptr<GameState> nextState);

	void quit();

	polymorph::sys::UISystem& uiSystem() { return _uiSys; }
	polymorph::sys::GraphicsSystem& graphicsSystem() { return _grSys; }
	polymorph::sys::NTSystem<GameRunner>& system() { return _parentSystem; }

private:
	polymorph::sys::UISystem&				_uiSys;
	polymorph::sys::GraphicsSystem&			_grSys;
	polymorph::sys::NTSystem<GameRunner>&	_parentSystem;

	bool _quitting;

	std::shared_ptr<GameState> _state;
	std::shared_ptr<GameState> _nextState;
};

}

#endif