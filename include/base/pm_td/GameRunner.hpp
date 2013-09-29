#pragma once

#include "pm_td/GameState.hpp"

#include "pm_td/GameScene.hpp"

#include <sys/NTSystem.hpp>
#include <sys/UISystem.hpp>
#include <sys/GraphicsSystem.hpp>

#include <NonCopyable.hpp>

#include <memory>

namespace polymorph { namespace pm_td {

class GameRunner : NonCopyable
{
public:
	struct ConstructionArgs {};

	GameRunner(ConstructionArgs&&, sys::NTSystem<GameRunner>& system);

	~GameRunner();

	bool update(TimeDuration dt);

	void setState(GameState&& nextState);

	void quit();

	sys::NTSystem<GameRunner>& system() { return _parentSystem; }

	GameScene& gameScene() { return _gameScene; }

private:
	sys::NTSystem<GameRunner>&	_parentSystem;

	bool _quitting;

	GameScene _gameScene;

	GameState _state;
	GameState _nextState;
};

} }