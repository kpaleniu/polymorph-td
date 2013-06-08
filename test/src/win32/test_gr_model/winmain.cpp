#include <windows.h>

#include "gr/TestWindow.hpp"

#include <gr/TextureManager.hpp>
#include <gr/Renderer.hpp>
#include <gr/Mesh.hpp>
#include <gr/MeshIO.hpp>
#include <gr/MeshManager.hpp>
#include <gr/Model.hpp>

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

		gr::MeshManager meshManager;

		text::string_hash meshId = text::hash("TEST_MESH");
		auto meshHandle = meshManager.addMesh(meshId, std::move(getMesh()));

		std::vector<gr::Model::ModelMesh> meshes;
		gr::Model::ModelMesh modelMesh = {gr::Transform(), meshHandle};

		meshes.push_back(modelMesh);

		gr::Model testModel(std::move(meshes));

		gr::real_t moveSpeed = 0.01f;

		while (updateTestWindow())
		{
			testModel.render(renderer);

			renderer.render();


			if (testModel.transform().translation()[0] > 1.0f
				|| testModel.transform().translation()[0] < -1.0f)
			{
				moveSpeed *= -1.0f;
			}

			testModel.transform() *= gr::Transform::translate(moveSpeed, 0);
		}
	}

	destroyTestWindow();

	return 0;
}