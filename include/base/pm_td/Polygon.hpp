#pragma once

#include "pm_td/ColorType.hpp"
#include "pm_td/GameScene.hpp"

#include <gr/Scene.hpp>
#include <sys/GraphicsSystem.hpp>

#include <NonCopyable.hpp>

namespace polymorph { namespace pm_td {

class Polygon : NonCopyable
{
public:
	Polygon(GameScene& scene,
			gr::Scene<gr::Transform2>::model_id model, 
			ColorType type, 
			unsigned short hp);

	Polygon(Polygon&& other);

	~Polygon();

	ColorType type() const;
	unsigned short hp() const;
	GameScene::model_id modelId() const;

	static std::size_t meshId(ColorType type, unsigned short hp);

private:
	ColorType _type;
	unsigned short _hp;
	
	GameScene::model_id _model;
	GameScene&			_scene;
};

} }