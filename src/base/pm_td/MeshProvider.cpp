#include "pm_td/MeshProvider.hpp"

#include <filesystem/FileInputStream.hpp>
#include <filesystem/FileOutputStream.hpp>

#include <Assert.hpp>
#include <Debug.hpp>

namespace polymorph { namespace pm_td {

namespace {

gr::Mesh createPolygonMesh(unsigned short vertCount,
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

gr::Mesh createRedLightTowerMesh(gr::real_t thickness, 
								 const gr::real_t* redColor)
{
	std::vector<gr::real_t> vertices =
	{
		-0.5f,  thickness,
		-0.5f, -thickness,
		 0.5f, -thickness,
		 0.5f,  thickness,

		 thickness,  0.5f,
		-thickness,  0.5f,
		-thickness, -0.5f,
		 thickness, -0.5f
	};


	std::vector<gr::index_t> indices =	
	{
		0, 1, 2, 3,
		4, 5, 6, 7
	};


	std::vector<gr::real_t> colors;
	colors.reserve(3 * 8);

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 3; ++j)
			colors.push_back(redColor[j]);
	}

	gr::VertexList vl(gr::VertexFormat::V2_C3, 
					  std::move(vertices), 
					  std::move(colors));

	gr::Mesh rMesh(std::move(vl), gr::Primitive::QUADS);

	rMesh.addSubMesh(nullptr, std::move(indices));

	return rMesh;
}

const char* LOG_TAG = "MeshProvider";

}


gr::Mesh MeshProvider::loadPolygonMesh(const gr::TextureManager& texManager,
									   unsigned short vertices, 
									   ColorType type)
{
	std::string path = pathToPolygonMesh(vertices, type);

	try
	{
		filesystem::FileInputStream fis(path);
		return gr::MeshIO::readMesh(fis, texManager);
	}
	catch (io::IOException&)
	{
		INFO_OUT(LOG_TAG, "Loading %s failed, re-creating.", path.c_str());

		const auto& typeData = getColorTypeData(type);
		gr::Mesh rMesh = createPolygonMesh(vertices, 0.5f, 0.1f, typeData.color);

		try
		{
			filesystem::FileOutputStream fos(path);
			gr::MeshIO::writeMesh(fos, rMesh);
		}
		catch (io::IOException&)
		{
			ERROR_OUT(LOG_TAG, "Failed to save mesh to file.");
		}

		return rMesh;
	}
}

gr::Mesh MeshProvider::loadTowerMesh(const gr::TextureManager& texManager,
									 unsigned short upgrade,
									 ColorType type)
{
	std::string path = pathToTowerMesh(upgrade, type);

	try
	{
		filesystem::FileInputStream fis(path);
		return gr::MeshIO::readMesh(fis, texManager);
	}
	catch (io::IOException&)
	{
		INFO_OUT(LOG_TAG, "Loading %s failed, re-creating.", path.c_str());

		// TODO Implement mo' towers!
		
		const auto& typeData = getColorTypeData(type);

		gr::Mesh rMesh = createRedLightTowerMesh(0.05f, typeData.color);

		try
		{
			filesystem::FileOutputStream fos(path);
			gr::MeshIO::writeMesh(fos, rMesh);
		}
		catch (io::IOException&)
		{
			ERROR_OUT(LOG_TAG, "Failed to save mesh to file.");
		}

		return rMesh;
	}
}

std::string MeshProvider::pathToPolygonMesh(unsigned short vertices, ColorType type)
{
	const auto& typeData = getColorTypeData(type);
	
	return "Polygon_" 
		   + std::to_string(vertices) 
		   + "_" 
		   + typeData.typeName 
		   + ".mesh";
}

std::string MeshProvider::pathToTowerMesh(unsigned short upgrade, ColorType type)
{
	const auto& typeData = getColorTypeData(type);

	return "Tower_"
			+ std::to_string(upgrade)
			+ "_"
			+ typeData.typeName
			+ ".mesh";
}

} }