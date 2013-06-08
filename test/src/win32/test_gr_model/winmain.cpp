#include <windows.h>

#include "gr/TestWindow.hpp"

#include <gr/TextureManager.hpp>
#include <gr/Renderer.hpp>
#include <gr/Mesh.hpp>
#include <gr/MeshIO.hpp>

#include <filesystem/FileOutputStream.hpp>
#include <filesystem/FileInputStream.hpp>

gr::Mesh createTestQuad()
{
	std::vector<gr::real_t> vertices;

	vertices.push_back(-0.5f); vertices.push_back(-0.5f);
	vertices.push_back( 0.5f); vertices.push_back(-0.5f);
	vertices.push_back( 0.5f); vertices.push_back( 0.5f);
	vertices.push_back(-0.5f); vertices.push_back( 0.5f);

	std::vector<gr::real_t> colors;

	colors.push_back(0.0f); colors.push_back(0.0f); colors.push_back(0.5f); 
	colors.push_back(1.0f); colors.push_back(0.0f); colors.push_back(0.5f); 
	colors.push_back(1.0f); colors.push_back(1.0f); colors.push_back(0.5f); 
	colors.push_back(0.0f); colors.push_back(1.0f); colors.push_back(0.5f); 

	std::vector<gr::index_t> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);

	gr::VertexList vl(gr::VertexFormat::V2_C3, std::move(vertices), std::move(colors));

	gr::Mesh quadMesh(std::move(vl), gr::Primitive::QUADS);
	quadMesh.addSubMesh(gr::TextureManager::getNullTexture(), std::move(indices));

	return quadMesh;
}

gr::Mesh getMesh()
{
	gr::TextureManager textureManager;

	try
	{
		filesystem::FileInputStream fis("TestQuad.mesh");

		return gr::MeshIO::readMesh(fis, textureManager);
	}
	catch (filesystem::FileException& e)
	{
		auto mesh = createTestQuad();

		try
		{
			filesystem::FileOutputStream fos("TestQuad.mesh");

			gr::MeshIO::writeMesh(fos, mesh);
		}
		catch (filesystem::FileException& e)
		{
		}

		return mesh;
	}
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE, LPSTR , int)
{
	createTestWindow(hInstance);

	{
		auto surface = createSurface();
		gr::Renderer renderer(surface);

		auto quadMesh = getMesh();

		while (updateTestWindow())
		{
			quadMesh.render(renderer, gr::Transform::translate(1.0f, 0.0f, 0.0f));

			renderer.render();
		}
	}

	destroyTestWindow();

	return 0;
}