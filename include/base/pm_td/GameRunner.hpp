#ifndef PMTD_GAMERUNNER_HPP_
#define PMTD_GAMERUNNER_HPP_

#include "pm_td/GameState.hpp"

#include <sys/NTSystem.hpp>
#include <sys/UISystem.hpp>
#include <sys/GraphicsSystem.hpp>

#include <NonCopyable.hpp>

#include <memory>

namespace pm_td {

class GameRunner : NonCopyable
{
public:
	struct ConstructionArgs : ::NonCopyable
	{
		ConstructionArgs(polymorph::sys::UISystem& uiSys_,
						 polymorph::sys::GraphicsSystem& grSys_);

		ConstructionArgs(ConstructionArgs&& other);

		polymorph::sys::UISystem&		uiSys;
		polymorph::sys::GraphicsSystem& grSys;
	};


	GameRunner(ConstructionArgs&& args,
			   polymorph::sys::NTSystem<GameRunner>& system);

	~GameRunner();

	bool update(TimeDuration dt);

	void setState(GameState&& nextState);

	void quit();

	polymorph::sys::UISystem& uiSystem() { return _uiSys; }
	polymorph::sys::GraphicsSystem& graphicsSystem() { return _grSys; }
	polymorph::sys::NTSystem<GameRunner>& system() { return _parentSystem; }

private:
	polymorph::sys::UISystem&				_uiSys;
	polymorph::sys::GraphicsSystem&			_grSys;
	polymorph::sys::NTSystem<GameRunner>&	_parentSystem;

	bool _quitting;

	GameState _state;
	GameState _nextState;
};

}

#endif