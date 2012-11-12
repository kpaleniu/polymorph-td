/**
 * @file Game.cpp
 *
 */

#include "game/Game.hpp"

#include "sys/GraphicsSystem.hpp"
#include "sys/UISystem.hpp"

using namespace sys;

namespace game {

Game::Game(UISystem& uiSystem, GraphicsSystem& grSystem)
:	_uiSystem(uiSystem),
 	_grSystem(grSystem)
{}

Game::~Game()
{}

int Game::enter()
{


	return 0;
}


}
