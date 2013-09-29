#include "pm_td/Enemy.hpp"

#include "pm_td/MeshProvider.hpp"

#include <gr/TextureManager.hpp>

namespace polymorph { namespace pm_td {

namespace {

gr::Scene<gr::Transform2>::model_id getModelId(std::size_t enemyId,
											   unsigned short layer)
{
	return enemyId * 2 + layer;
}

}

//

Enemy::AnimatedPolygon::AnimatedPolygon(GameScene& scene,
										Polygon&& polygon_, 
										ModelAnimator&& animator_)
:	polygon(std::move(polygon_)),
	animator(std::move(animator_))
{
	auto& model = scene.model(polygon.modelId());
	animator.attach(model);
}

Enemy::AnimatedPolygon::AnimatedPolygon(AnimatedPolygon && other)
:	polygon(std::move(other.polygon)),
	animator(std::move(other.animator))
{
}

void Enemy::AnimatedPolygon::update(GameScene& scene, TimeDuration dt)
{
	auto& model = scene.model(polygon.modelId());
	animator.update(dt, model);
}

//

void Enemy::NormalAnimator::attach(gr::Model<gr::Transform2>& model)
{
	model.transform().scale() = scale;
}

void Enemy::NormalAnimator::update(TimeDuration dt,
								   gr::Model<gr::Transform2>& model)
{
	model.transform().rotation() += angularVelocity * dt.toSecs();
}

//

Enemy::Enemy(GameScene& scene,
			 gr::real_t speed,
			 std::size_t id,
			 const Path& path,
			 const LayerDatas& datas,
			 Listener* listener)
:	_polygons(),
	_speed(speed),
	_id(id),
	_scene(scene),
	_pathPoint(path.getStart()),
	_listener(listener)
{
	ASSERT(_id != 0, "Unit requires non-zero model id.");

	for (unsigned short i = 0; i < datas.size(); ++i)
	{
		Polygon polygon(_scene,
						getModelId(_id, i),
						datas[i].type,
						datas[i].hp);

		AnimatedPolygon animatedPolygon
		(
			scene,
			std::move(polygon),
			NormalAnimator
			{
				1.0f / gr::real_t(1 + i), 
				(i % 2 == 0 ? HALF_PI : -HALF_PI)
			}
		);

		_polygons.push_back(std::move(animatedPolygon));
	}
}

Enemy::Enemy(Enemy&& other)
:	_polygons(std::move(other._polygons)),
	_speed(other._speed),
	_id(other._id),
	_scene(other._scene),
	_pathPoint(std::move(other._pathPoint)),
	_listener(other._listener)
{
	other._id = 0;
}

std::size_t Enemy::id() const
{
	return _id;
}

void Enemy::update(TimeDuration dt)
{
	if (_pathPoint.reachedEnd())
	{
		if (_listener != nullptr)
			_listener->onReachedEnd(*this);
	}

	_pathPoint.advance(dt.toSecs() * _speed);

	for (auto& polygon : _polygons)
	{
		auto& model = _scene.model(polygon.polygon.modelId());

		model.transform().translation() = _pathPoint.currentPosition();

		polygon.update(_scene, dt);
	}
}

const gr::real_t& Enemy::speed() const
{
	return _speed;
}

gr::real_t& Enemy::speed()
{
	return _speed;
}

void Enemy::loadMeshes(GameScene& gameScene, const LayerDatas& layerTypes)
{
	// TODO Implement textures
	static gr::TextureManager dummyTexManager;

	for (const auto& layerData : layerTypes)
	{
		for (unsigned short i = 1; i <= layerData.hp; ++i)
		{
			auto meshHash = Polygon::meshId(layerData.type, i);

			if (gameScene.hasMesh(meshHash))
				continue;

			auto mesh = MeshProvider::loadPolygonMesh(dummyTexManager,
													  i + 2,
													  layerData.type);

			gameScene.addMesh(meshHash, std::move(mesh));
		}
	}
}

} }