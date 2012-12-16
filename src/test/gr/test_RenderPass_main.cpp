
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


		RenderPass::BufferDesc bufferDesc1;
		bufferDesc1.clearFlags = enum_t(BufferFlag::COLOR);
		bufferDesc1.useFlags = enum_t(BufferFlag::COLOR);

		RenderPass::BufferDesc bufferDesc2;
		bufferDesc2.clearFlags = enum_t(BufferFlag::NONE);
		bufferDesc2.useFlags = enum_t(BufferFlag::COLOR);

		RenderPass::MaterialDesc materialDesc;
		materialDesc.shader = nullptr;
		materialDesc.texture = nullptr;

		RenderPass::TransformDesc transformDesc1 =
		{
			Projection::ortho(-1, 1, -1, 1, 1, -1),
			Transform::identity(),
			Transform::identity()
		};

		RenderPass::TransformDesc transformDesc2 =
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
		                 bufferDesc1,
		                 transformDesc1);
		RenderPass pass2(bufferManager,
		                 VertexFormat::V2,
		                 Primitive::TRIANGLES,
		                 materialDesc,
		                 bufferDesc2,
		                 transformDesc2);

		TestVertexSupplier testVS;
		auto vsHandle1 = pass1.addVertexSupplier(testVS);
		/*auto vsHandle2 = */pass2.addVertexSupplier(testVS);

		int i = 0;
		while (updateTestWindow())
		{
			pass1.render();
			pass2.render();

			surface.flipBuffers();

			if (++i == 500)
				pass1.removeVertexSupplier(vsHandle1);
			if (i == 2000)
				vsHandle1 = pass1.addVertexSupplier(testVS);
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
