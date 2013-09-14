#include "pm_td/EnemyPolygon.hpp"

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

	static char buffer[] = "PolygonMeshHash###";

	buffer[sizeof(buffer) - 3] = vertCount & 0x00ff;
	buffer[sizeof(buffer) - 2] = (vertCount & 0xff00) >> 8;
	buffer[sizeof(buffer) - 1] = char(enemyType);

	return text::hash(buffer);
}

}


EnemyPolygon::EnemyPolygon(polymorph::sys::GraphicsSystem& grSys,
						   std::size_t id, 
						   const Path& path,
						   LayerData data,
						   Listener* listener)
:	_model(id),
	_hp(data.hp),
	_grSys(grSys),
	_pathPoint(path.getStart()),
	_listener(listener)
{
	ASSERT(id != 0, "Unit requires non-zero model id.");

	auto sceneMutator = grSys.sceneMutator();

	//auto mesh = sceneMutator.meshes.getMesh(polyMeshHash(hp + 2));

	auto& meshManager = sceneMutator.meshes;

	auto mesh = meshManager.addMesh(polyMeshHash(_hp + 2, data.type),
									createMeshPolygon(_hp + 2,
													  0.5f,
													  0.1f,
													  getEnemyColorRGB(data.type)));

	gr::Model<gr::Transform2>
		model(std::vector<gr::Model<gr::Transform2>::ModelMesh>
			  { {gr::Transform2::IDENTITY, mesh} });

	model.transform().translation() = _pathPoint.currentPosition();

	sceneMutator.scene.addModel(_model, std::move(model));
}

EnemyPolygon::EnemyPolygon(EnemyPolygon&& other)
:	_model(other._model),
	_hp(other._hp),
	_grSys(other._grSys),
	_pathPoint(std::move(other._pathPoint)),
	_listener(other._listener)
{
	other._model = 0;
}

EnemyPolygon::~EnemyPolygon()
{
	if (_model)
	{
		auto sceneMutator = _grSys.sceneMutator();
		sceneMutator.scene.removeModel(_model);
	}
}

std::size_t EnemyPolygon::id() const
{
	return _model;
}

void EnemyPolygon::update(TimeDuration dt)
{
	if (_pathPoint.reachedEnd())
	{
		if (_listener != nullptr)
			_listener->onReachedEnd(*this);
	}

	_pathPoint.advance(dt.toMillis() * 0.0005f);

	{
		auto sceneMutator = _grSys.sceneMutator();

		auto& thisModel = sceneMutator.scene.model(_model);
		
		thisModel.transform().rotation() += PI * 0.0005f * dt.toMillis();
		thisModel.transform().translation() = _pathPoint.currentPosition();
	}

}

}