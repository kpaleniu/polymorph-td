
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


		RenderPass::BufferDesc bufferDesc;
		bufferDesc.clearFlags = enum_t(BufferFlag::COLOR);
		bufferDesc.useFlags = enum_t(BufferFlag::COLOR);

		RenderPass::MaterialDesc materialDesc;
		materialDesc.shader = nullptr;
		materialDesc.texture = nullptr;

		RenderPass::TransformDesc transformDesc =
		{
			Projection::ortho(0, 1, 0, 1, 1, -1),
			Transform::scale(0.5f) * Transform::rotateAxis(Vector3_r(std::array<real_t, 3>{{0, 0, 1}}),
			                                               math::QUARTER_PI),
			Transform::identity()
		};

		RenderPass pass1(bufferManager,
		                 VertexFormat::V2,
		                 Primitive::TRIANGLES,
		                 materialDesc,
		                 bufferDesc,
		                 transformDesc);

		TestVertexSupplier testVS;
		auto vsHandle = pass1.addVertexSupplier(testVS);

		int i = 0;
		while (updateTestWindow())
		{
			pass1.render();

			surface.flipBuffers();

			if (++i == 500)
				pass1.removeVertexSupplier(vsHandle);
			if (i == 2000)
				vsHandle = pass1.addVertexSupplier(testVS);
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
