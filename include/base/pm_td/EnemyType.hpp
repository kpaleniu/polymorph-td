#ifndef PMTD_ENEMY_TYPE_HPP_
#define PMTD_ENEMY_TYPE_HPP_

#include <gr/types.hpp>

namespace pm_td {

enum class EnemyType : char
{
	RED = 0,
	GREEN,
	BLUE,
	WHITE
};

const gr::real_t* getEnemyColorRGB(EnemyType enemyType);

}

#endif