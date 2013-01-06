
#include "resource/ImageReader.hpp"
#include "gr/TestWindow.hpp"

#include <gr/RenderPass.hpp>
#include <gr/opengl.hpp>
#include <gr/Texture.hpp>
#include <gr/Sprite.hpp>
#include <gr/SpriteSheet.hpp>

#include <text/util.hpp>

#include <Debug.hpp>

// print tag
namespace {

const char* TAG = "GUITest";

}

/**
 * Windows main.
 */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE, LPSTR, int)
{
	using namespace gr;
	using namespace resource;

	DEBUG_OUT(::TAG, "Starting test");

	createTestWindow(hInstance);

	try
	{
		static text::string_hash urlHash = text::intern( R"(.\data\images\test.png)" );
		static text::string_hash spriteHash = text::intern("test_sprite");

		auto surface = createSurface();

		ImageReader imReader;
		auto imageHandle = imReader.getImage(urlHash);

		const std::map<SpriteSheet::sprite_id_t, Rect<unsigned int>> spriteAreas =
		{
			std::make_pair( spriteHash,
			                Rect<unsigned int>(0, 0,
			                                  imageHandle->getWidth(),
			                                  imageHandle->getHeight()) )
		};

		SpriteSheet spriteSheet(*imageHandle, spriteAreas);

		BufferManager bufferManager;

		RenderPass::BufferDesc bufferDesc;
		bufferDesc.clearFlags = enum_t(BufferFlag::COLOR);
		bufferDesc.useFlags = enum_t(BufferFlag::COLOR);

		RenderPass::MaterialDesc materialDesc =
		{
			&spriteSheet.texture(),
			nullptr
		};

		RenderPass::TransformDesc transformDesc =
		{
			Projection::ortho(-1, 1, -1, 1, 1, -1),
			Transform::identity(),
			Transform::identity()
		};


		RenderPass pass( bufferManager,
		                 VertexFormat::V2_T2,
		                 Primitive::QUADS,
		                 materialDesc,
		                 bufferDesc,
		                 transformDesc );

		Sprite testSprite(spriteSheet.coordsFor(spriteHash));

		pass.addVertexSupplier(testSprite);

		while (updateTestWindow())
		{
			//pass.updateVertices();
			pass.render();

			surface.flipBuffers();
		}


	}
	catch (std::exception& e)
	{
		DEBUG_OUT(::TAG, e.what());
	}
	catch (...)
	{
		DEBUG_OUT(::TAG, "Error");
	}

	destroyTestWindow();

	DEBUG_OUT(::TAG, "Closing");

	return 0;
}
