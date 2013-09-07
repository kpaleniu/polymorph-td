#include "pm_td/PlayState.hpp"

#include "pm_td/GameRunner.hpp"

#include <text/util.hpp>
#include <gr/Mesh.hpp>

#include <Assert.hpp>
#include <Debug.hpp>

#include <vector>
#include <cmath>

#include <algorithm>

namespace {

const text::string_hash polyMeshHash(unsigned short vertCount)
{
	ASSERT(vertCount > 2, "Too few vertices to create polygon.");

	char buffer[] = "PolygonMeshHash##";
	buffer[sizeof(buffer) - 2] = vertCount & 0x00ff;
	buffer[sizeof(buffer) - 1] = (vertCount & 0xff00) >> 2;

	return text::hash(buffer);
}

gr::Mesh createMeshPolygon(unsigned short vertCount, 
						   gr::real_t radius, 
						   gr::real_t thickness,
						   gr::TextureManager::TextureHandle texture)
{
	ASSERT(vertCount > 2, "Too few vertices to create polygon.");

	std::vector<gr::real_t> vertices;
	vertices.reserve(vertCount * 2 * 2);

	std::vector<gr::index_t> indices;
	indices.reserve(vertCount * 2);

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

		vertices.push_back(inX);
		vertices.push_back(inY);
		vertices.push_back(outX);
		vertices.push_back(outY);

		indices.push_back(2 * i);
		indices.push_back(2 * i + 1);
		indices.push_back(2 * ((i+1) % vertCount) + 1);
		indices.push_back(2 * ((i+1) % vertCount));
	}

	gr::VertexList vl(gr::VertexFormat::V2, std::move(vertices));
	ASSERT(vl.vertexCount() == vertCount * 2, "Somethings is iffy...");

	gr::Mesh rMesh(std::move(vl), gr::Primitive::QUADS);

	rMesh.addSubMesh(texture, std::move(indices));

	return rMesh;
}


}

namespace pm_td {

void PlayState::enterState(GameRunner& runner)
{
	_initialized = false;

	runner.graphicsSystem().actionQueue().pushAction
	(
		[this, &runner](polymorph::sys::GraphicsSystemRunner& grRunner)
		{
			for (unsigned short j = 0; j < 4; ++j)
			{
				for (unsigned short i = 0; i < 4; ++i)
				{
					// Add meshes

					gr::Mesh polyMesh =
						createMeshPolygon(4 * j + i + 3,
										  0.125f,
										  0.01f,
										  gr::TextureManager::getNullTexture());

					auto meshHandle =
						grRunner.meshManager().addMesh(polyMeshHash(4 * j + i + 3),
													   std::move(polyMesh));

					{
						auto sceneMutator = runner.graphicsSystem().sceneMutator();

						gr::Model<gr::Transform2> polyModel
						(
							std::vector<gr::Model<gr::Transform2>::ModelMesh>
							{ {
								gr::Transform2::IDENTITY,
								meshHandle
							} }
						);

						polyModel.transform().translation() =
							gr::Vector2_r
							{
								0.33f * (i - 2.0f),
								0.33f * (j - 2.0f)
							};

						sceneMutator.scene.addModel(4 * j + i + 1, 
													std::move(polyModel));
					}

				}
			}

			_initialized = true;
		}
	);
}

void PlayState::exitState(GameRunner& runner)
{
	auto sceneMutator = runner.graphicsSystem().sceneMutator();

	_initialized = false;

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			sceneMutator.scene.removeModel(4 * j + i + 1);
}

void PlayState::update(GameRunner& runner, TimeDuration dt)
{
	if (_initialized)
	{
		{
			auto sceneMutator = runner.graphicsSystem().sceneMutator();

			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					auto& poly = sceneMutator.scene.model(4 * j + i + 1);
					poly.transform().rotation() += PI * 0.0005f * dt.toMillis();
				}
			}
		}
	}
}

}