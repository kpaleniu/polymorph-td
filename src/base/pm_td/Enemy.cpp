#include "pm_td/Enemy.hpp"

namespace pm_td {

namespace {

gr::Mesh createMeshPolygon(unsigned short vertCount,
						   gr::real_t radius,
						   gr::real_t thickness,
						   const gr::real_t* rgbColor)
{
	ASSERT(vertCount > 2, "Too few vertices to create polygon.");

	std::vector<gr::real_t> vertices;
	vertices.reserve(vertCount * 2 * 2);

	std::vector<gr::index_t> indices;
	indices.reserve(vertCount * 2);

	std::vector<gr::real_t> colors;
	colors.reserve(vertCount * 3);

	gr::real_t innerRad = radius - 0.5f * thickness;
	gr::real_t outerRad = radius + 0.5f * thickness;

	gr::real_t radian = 0.0f;
	for (unsigned short i = 0; i < vertCount; ++i, radian += TWO_PI / vertCount)
	{
		gr::real_t cosRad = std::cos(radian);
		gr::real_t sinRad = std::sin(radian);

		gr::real_t inX = innerRad * cosRad;
		gr::real_t inY = innerRad * sinRad;

		gr::real_t outX = outerRad * cosRad;
		gr::real_t outY = outerRad * sinRad;

		
		colors.push_back(rgbColor[0]);
		colors.push_back(rgbColor[1]);
		colors.push_back(rgbColor[2]);

		vertices.push_back(inX);
		vertices.push_back(inY);

		
		colors.push_back(rgbColor[0]);
		colors.push_back(rgbColor[1]);
		colors.push_back(rgbColor[2]);

		vertices.push_back(outX);
		vertices.push_back(outY);


		indices.push_back(2 * i);
		indices.push_back(2 * i + 1);
		indices.push_back(2 * ((i + 1) % vertCount) + 1);
		indices.push_back(2 * ((i + 1) % vertCount));
	}

	gr::VertexList vl(gr::VertexFormat::V2_C3,
					  std::move(vertices),
					  std::move(colors));

	gr::Mesh rMesh(std::move(vl), gr::Primitive::QUADS);

	rMesh.addSubMesh(nullptr, std::move(indices));

	return rMesh;
}

text::string_hash polyMeshHash(unsigned short vertCount,
							   EnemyType enemyType)
{
	ASSERT(vertCount > 2, "Too few vertices to create polygon.");

	static const text::string_hash hash = text::hash("PolygonMeshHash");

	auto rHash = hash;

	rHash += vertCount;
	rHash += (int(enemyType) << 8);

	DEBUG_OUT("PolyHash", "Hashing (%i, %i): %i", int(vertCount), int(enemyType), int(rHash));

	return rHash;
}

gr::Scene<gr::Transform2>::model_id getModelId(std::size_t enemyPolygonId,
											   unsigned short layer)
{
	return enemyPolygonId * 2 + layer;
}

}


Enemy::Layer::Layer(LayerData initialData_,
				    gr::Scene<gr::Transform2>::model_id modelId_)
:	initialData(initialData_),
	modelId(modelId_),
	hp(initialData.hp)
{
}



Enemy::Enemy(polymorph::sys::GraphicsSystem& grSys,
						   std::size_t id, 
						   const Path& path,
						   LayerData data,
						   Listener* listener)
:	_layers{ { Layer(data, getModelId(id, 0)) } },
	_id(id),
	_grSys(grSys),
	_pathPoint(path.getStart()),
	_listener(listener)
{
	ASSERT(_id != 0, "Unit requires non-zero model id.");

	auto sceneMutator = grSys.sceneMutator();
	auto& meshManager = sceneMutator.meshes;
	auto& scene		  = sceneMutator.scene;

	ASSERT(meshManager.hasMesh(polyMeshHash(data.hp + 2, data.type)),
		   "Mesh is not loaded, did you forget to call 'loadMeshes'?.");

	auto meshHandle = meshManager.getMesh( polyMeshHash(data.hp + 2, data.type) );

	gr::Model<gr::Transform2>
		model(std::vector<gr::Model<gr::Transform2>::ModelMesh>
			  { {gr::Transform2::IDENTITY, meshHandle} });

	model.transform().translation() = _pathPoint.currentPosition();
	model.transform().scale() = 1.0f;

	scene.addModel(_layers[0].modelId, std::move(model));
}

Enemy::Enemy(polymorph::sys::GraphicsSystem& grSys,
						   std::size_t id,
						   const Path& path,
						   const LayerDatas& data,
						   Listener* listener)
:	_layers(),
	_id(id),
	_grSys(grSys),
	_pathPoint(path.getStart()),
	_listener(listener)
{
	ASSERT(_id != 0, "Unit requires non-zero model id.");

	for (unsigned short i = 0; i < data.size(); ++i)
		_layers.push_back(Layer(data[i], getModelId(id, i)));

	{
		auto sceneMutator = grSys.sceneMutator();
		auto& meshManager = sceneMutator.meshes;
		auto& scene = sceneMutator.scene;

		for (unsigned int i = 0; i < data.size(); ++i)
		{
			auto meshHandle = meshManager.getMesh(polyMeshHash(data[i].hp + 2,
				data[i].type));

			gr::Model<gr::Transform2>
				model(std::vector<gr::Model<gr::Transform2>::ModelMesh>
			{ {gr::Transform2::IDENTITY, meshHandle} });

			model.transform().translation() = _pathPoint.currentPosition();
			model.transform().scale() = 0.8f * gr::real_t(data.size() - (i + 1)) + 0.5f;

			scene.addModel(_layers[i].modelId, std::move(model));
		}
	}
}

Enemy::Enemy(Enemy&& other)
:	_layers(other._layers),
	_id(other._id),
	_grSys(other._grSys),
	_pathPoint(std::move(other._pathPoint)),
	_listener(other._listener)
{
	for (auto& layer : other._layers)
		layer.modelId = 0;
	
	other._id = 0;
}

Enemy::~Enemy()
{
	if (!_id)
		return;

	auto sceneMutator = _grSys.sceneMutator();

	for (const auto& layer : _layers)
		sceneMutator.scene.removeModel(layer.modelId);
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

	_pathPoint.advance(dt.toMillis() * 0.0005f);

	{
		auto sceneMutator = _grSys.sceneMutator();

		for (unsigned int i = 0; i < _layers.size(); ++i)
		{
			auto& thisModel = sceneMutator.scene.model(_layers[i].modelId);

			if (i % 2 == 0)
				thisModel.transform().rotation() -= PI * 0.0005f * dt.toMillis();
			else
				thisModel.transform().rotation() += PI * 0.0005f * dt.toMillis();

			thisModel.transform().translation() = _pathPoint.currentPosition();
		}
	}

}

void Enemy::loadMeshes(gr::MeshManager& meshManager,
							  const std::vector<LayerData>& layerTypes)
{
	// TODO Move data someplace else.
	static const gr::real_t radius = 0.5f;
	static const gr::real_t thickness = 0.1f;


	for (const auto& layerData : layerTypes)
	{
		for (unsigned short i = 1; i <= layerData.hp; ++i)
		{
			auto meshHash = polyMeshHash(i + 2, layerData.type);

			if (meshManager.hasMesh(meshHash))
				continue;

			DEBUG_OUT("Enemy",
					  "Creating mesh %i (%i, %i)",
					  int(meshHash), int(i), int(layerData.type));

			auto mesh = createMeshPolygon(i + 2,
										  radius,
										  thickness,
										  getEnemyColorRGB(layerData.type));

			meshManager.addMesh(meshHash, std::move(mesh));
		}
	}
}

}