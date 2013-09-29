#include "pm_td/Tower.hpp"

#include "pm_td/MeshProvider.hpp"

#include <sys/Systems.hpp>

namespace polymorph { namespace pm_td {

Tower::Tower(GameScene& scene,
			 TypeData typeData,
			 std::size_t id,
			 TimeDuration attackCooldown)
:	_scene(scene),
	_typeData(typeData),
	_attackCooldown(attackCooldown),
	_id(id * 2)
{
	gr::TextureManager dummyTexManager;

	auto handle = _scene.addMesh
	(
		512, // HASH IT BOY!
		MeshProvider::loadTowerMesh
		(
			dummyTexManager, 
			_typeData.upgrade, 
			_typeData.type
		)
	);

	gr::Model<gr::Transform2> thisModel
	(
		std::vector<gr::Model<gr::Transform2>::ModelMesh>
		{{gr::Transform2::IDENTITY, handle}}
	);

	_scene.addModel(_id, std::move(thisModel));
}

Tower::Tower(Tower&& other)
:	_scene(other._scene),
	_typeData(other._typeData),
	_attackCooldown(other._attackCooldown),
	_id(other._id)
{
	other._id = 0;
}

Tower::~Tower()
{
	if (_id)
		_scene.removeModel(_id);
}

void Tower::update(TimeDuration /*dt*/)
{
	// TODO Implement
}

} }