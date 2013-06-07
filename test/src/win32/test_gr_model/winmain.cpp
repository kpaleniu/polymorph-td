#include <windows.h>

#include "gr/TestWindow.hpp"

#include <gr/TextureManager.hpp>
#include <gr/Renderer.hpp>
#include <gr/Mesh.hpp>

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
	quadMesh.addSubMesh(gr::TextureManager::TextureHandle(), std::move(indices));

	return quadMesh;
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE, LPSTR , int)
{
	createTestWindow(hInstance);

	{
		auto surface = createSurface();
		gr::Renderer renderer(surface);

		auto quadMesh = createTestQuad();

		while (updateTestWindow())
		{
			quadMesh.render(renderer, gr::Transform::translate(1.0f, 0.0f, 0.0f));

			// renderer.debugDraw().drawLine2D(0, 0, 1, 1);

			renderer.render();
		}
	}

	destroyTestWindow();

	return 0;
}