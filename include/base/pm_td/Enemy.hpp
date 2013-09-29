#pragma once

#include "pm_td/Path.hpp"
#include "pm_td/ColorType.hpp"
#include "pm_td/Polygon.hpp"
#include "pm_td/ModelAnimator.hpp"
#include "pm_td/GameScene.hpp"

#include <sys/GraphicsSystem.hpp>
#include <gr/Scene.hpp>

#include <NonCopyable.hpp>

#include <atomic>
#include <array>
#include <vector>

namespace polymorph { namespace pm_td {

class Enemy : NonCopyable
{
public:

	class Listener
	{
	public:
		virtual void onReachedEnd(const Enemy&) = 0;
	};

	struct LayerData
	{
		unsigned short hp;
		ColorType type;
	};

	typedef std::vector<LayerData> LayerDatas;

public:
	Enemy(GameScene& scene,
		  gr::real_t speed,
		  std::size_t id,
		  const Path& path,
		  const LayerDatas& datas,
		  Listener* listener = nullptr);

	Enemy(Enemy&& other);

	std::size_t id() const;

	void update(TimeDuration dt);

	const gr::real_t& speed() const;
	gr::real_t& speed();

	/** 
	 * Creates and loads all meshes used by polygons with specified layer types
	 * and all meshes with lower and equal hp than the specified.
	 */
	static void loadMeshes(GameScene& gameScene, const LayerDatas& layerTypes);

private:
	class AnimatedPolygon : ::NonCopyable
	{
	public:
		AnimatedPolygon(GameScene& scene,
						Polygon&& polygon_, 
						ModelAnimator&& animator_);

		AnimatedPolygon(AnimatedPolygon&& other);

		void update(GameScene& scene, TimeDuration dt);


		Polygon polygon;
		ModelAnimator animator;
	};

	struct NormalAnimator
	{
		void attach(gr::Model<gr::Transform2>& model);
		void update(TimeDuration dt, gr::Model<gr::Transform2>& model);

		gr::real_t scale;
		gr::real_t angularVelocity;
	};

	std::vector<AnimatedPolygon> _polygons;

	gr::real_t _speed;
	std::size_t _id;

	GameScene& _scene;

	PathPoint _pathPoint;

	Listener* _listener;
};

} }