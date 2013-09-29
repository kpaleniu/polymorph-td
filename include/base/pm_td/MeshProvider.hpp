#pragma once

#include <gr/Mesh.hpp>

#include "pm_td/ColorType.hpp"

#include <string>

namespace polymorph { namespace pm_td {

class MeshProvider
{
public:
	static gr::Mesh loadPolygonMesh(const gr::TextureManager& texManager,
									unsigned short vertices, 
									ColorType type);

	static gr::Mesh loadTowerMesh(const gr::TextureManager& texManager,
								  unsigned short upgrade,
								  ColorType type);

	static std::string pathToPolygonMesh(unsigned short vertices, ColorType type);

	static std::string pathToTowerMesh(unsigned short upgrade, ColorType type);
};

} }