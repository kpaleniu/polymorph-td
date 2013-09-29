#pragma once

#include "pm_td/ColorType.hpp"
#include "pm_td/GameScene.hpp"

#include <sys/GraphicsSystem.hpp>

#include <NonCopyable.hpp>

namespace polymorph { namespace pm_td {

class Tower : NonCopyable
{
public:
	struct TypeData
	{
		unsigned short upgrade;
		ColorType type;
	};

public:
	Tower(GameScene& scene,
		  TypeData typeData,
		  std::size_t id,
		  TimeDuration attackCooldown);

	Tower(Tower&& other);

	~Tower();

	void update(TimeDuration dt);

private:
	GameScene& _scene;
	TypeData _typeData;

	TimeDuration _attackCooldown;

	gr::Scene<gr::Transform2>::model_id _id;
};


} }