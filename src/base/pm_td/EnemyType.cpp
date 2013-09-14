#include "pm_td/EnemyType.hpp"

#define COLOR_CHANNELS 3

namespace pm_td {

namespace
{
	const gr::real_t colors[] =
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f
	};
}


const gr::real_t* getEnemyColorRGB(EnemyType enemyType)
{
	return &colors[unsigned int(enemyType) * COLOR_CHANNELS];
}


}

#undef COLOR_CHANNELS