
#include "gr/TestWindow.hpp"
#include "gr/RenderPass.hpp"
#include "gr/opengl.hpp"
#include "gr/BufferManager.hpp"
#include "gr/types.hpp"

#include <Debug.hpp>

// print tag
namespace {
const char* TAG = "RenderPassTestMain";
}

class TestVertexSupplier : public gr::VertexSupplier
{
public:
	void writeVertices(gr::VertexWriter& writer)
	{
		writer.vertices() << data;
		writer.indices() << ind;
	}

	std::vector<gr::real_t> data = { -0.5f, -0.5f,
								      0.5f, -0.5f,
								      0.5f,  0.5f };
	std::vector<gr::index_t> ind = {0, 1, 2};
};

/**
 * Windows main.
 */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE, LPSTR, int)
{
	using namespace gr;

	DEBUG_OUT(::TAG, "Starting test");

	createTestWindow(hInstance);

	try
	{
		auto surface = createSurface();
		BufferManager bufferManager;

		/*
		RenderPass::BufferDesc bufferDesc;
		bufferDesc.clearFlags = enum_t(BufferFlag::COLOR);
		bufferDesc.useFlags = enum_t(BufferFlag::COLOR);

		RenderPass::MaterialDesc materialDesc;
		materialDesc.shader = nullptr;
		materialDesc.texture = nullptr;

		RenderPass::TransformDesc transformDesc;
		transformDesc.modelTransform = { 1.0f, 0.0f, 0.0f, 0.0f,
		                                 0.0f, 1.0f, 0.0f, 0.0f,
										 0.0f, 0.0f, 1.0f, 0.0f,
		                                 0.0f, 0.0f, 0.0f, 1.0f };
		transformDesc.projTransform = { 1.0f, 0.0f, 0.0f, 0.0f,
		                                0.0f, 1.0f, 0.0f, 0.0f,
										0.0f, 0.0f, 1.0f, 0.0f,
		                                0.0f, 0.0f, 0.0f, 1.0f };
		transformDesc.viewTransform = { 1.0f, 0.0f, 0.0f, 0.0f,
									    0.0f, 1.0f, 0.0f, 0.0f,
									    0.0f, 0.0f, 1.0f, 0.0f,
									    0.0f, 0.0f, 0.0f, 1.0f };


		RenderPass pass1(bufferManager,
		                 Primitive::TRIANGLES,
		                 materialDesc,
		                 bufferDesc,
		                 transformDesc);
		 */


		RenderPass pass1(bufferManager, VertexFormat::V2);
		TestVertexSupplier testVS;
		pass1.addVertexSupplier(testVS);

		gl::enableClientState(GL_VERTEX_ARRAY);
		while (updateTestWindow())
		{
			glClear(GL_COLOR_BUFFER_BIT);

			pass1.render();

			surface.flipBuffers();
		}

	}
	catch (...)
	{
		DEBUG_OUT(::TAG, "Error");
	}

	destroyTestWindow();

	DEBUG_OUT(::TAG, "Closing");

	return 0;
}
