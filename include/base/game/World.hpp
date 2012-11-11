/**
 * @file World.hpp
 *
 */

#ifndef WORLD_HPP_
#define WORLD_HPP_

#include "game/Entity.hpp"
#include "text/util.hpp"

#include <vector>
#include <map>

namespace game {

class World
{
public:
	World();
	~World();

	EntityManager entityManager;
};


}


#endif /* WORLD_HPP_ */
