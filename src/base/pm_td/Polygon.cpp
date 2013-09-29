#include "pm_td/Polygon.hpp"

#include <Hasher.hpp>
#include <Assert.hpp>

namespace polymorph { namespace pm_td {

Polygon::Polygon(GameScene& scene,
				 gr::Scene<gr::Transform2>::model_id model,
				 ColorType type,
				 unsigned short hp)
:	_type(type),
	_hp(hp),
	_model(model),
	_scene(scene)
{
	if (model)
	{
		auto meshHandle = _scene.getMesh(meshId(_type, _hp));

		gr::Model<gr::Transform2> thisModel
		(
			std::vector<gr::Model<gr::Transform2>::ModelMesh>
			{ {gr::Transform2::IDENTITY, meshHandle} }
		);

		_scene.addModel(_model, std::move(thisModel));
	}
}

Polygon::Polygon(Polygon&& other)
:	_type(other._type),
	_hp(other._hp),
	_model(other._model),
	_scene(other._scene)
{
	other._model = 0;
}

Polygon::~Polygon()
{
	if (_model)
		_scene.removeModel(_model);
}


ColorType Polygon::type() const
{
	return _type;
}

unsigned short Polygon::hp() const
{
	return _hp;
}

gr::Scene<gr::Transform2>::model_id Polygon::modelId() const
{
	return _model;
}

std::size_t Polygon::meshId(ColorType type, unsigned short hp)
{
	static const std::size_t baseHash = hash("PolygonMeshHash");

	auto rHash = baseHash;

	rHash += hp + 2;
	rHash += (int(type) << 8);

	return rHash;
}

} }