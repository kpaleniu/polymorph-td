/**
 * @file Game.hpp
 *
 */

#ifndef GAME_HPP_
#define GAME_HPP_

namespace sys {
class UISystem;
class GraphicsSystem;
}

namespace game {

class Game
{
public:
	Game(sys::UISystem& uiSystem, sys::GraphicsSystem& grSys);
	~Game();

	int enter();

private:
	sys::UISystem& _uiSystem;
	sys::GraphicsSystem& _grSystem;
};

}


#endif /* GAME_HPP_ */
