#include <windows.h>

#include <sys/UISystem.hpp>
#include <text/util.hpp>

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


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE, LPSTR , int)
{
	polymorph::sys::Window::ConstructionData winCtorData;

	winCtorData.hInstance = hInstance;
	winCtorData.winRect.left = 256;
	winCtorData.winRect.top = 256;
	winCtorData.winRect.w = 800;
	winCtorData.winRect.h = 600;

	polymorph::sys::UISystem uiSys(std::move(winCtorData));
	uiSys.start();

	//
	gr::MeshManager meshManager;

	text::string_hash meshId = text::hash("TEST_MESH");
	auto meshHandle = meshManager.addMesh(meshId, std::move(createTestQuad()));

	std::vector<gr::Model::ModelMesh> meshes;
	gr::Model::ModelMesh modelMesh = {gr::Transform(), meshHandle};

	meshes.push_back(modelMesh);

	gr::Model testModel(std::move(meshes));
	//

	std::atomic<bool> lastSetVsync = true;

	const text::string_hash SWAP_VSYNC_HASH = text::hash("SWAP_VSYNC");

	const text::string_hash TEST_MODEL_HASH = text::hash("TEST_MODEL");
	const text::string_hash MOVE_MODEL_HASH = text::hash("MOVE_MODEL");

	const text::string_hash APP_EXIT_HASH = text::hash("APP_EXIT");
	const text::string_hash APP_HIDE_HASH = text::hash("APP_HIDE");

	const text::string_hash APP_POINTER_DOWN_HASH = text::hash("APP_POINTER_DOWN");
	const text::string_hash APP_POINTER_DRAG_HASH = text::hash("APP_POINTER_DRAG");
	const text::string_hash APP_POINTER_MOVE_HASH = text::hash("APP_POINTER_MOVE");
	const text::string_hash APP_POINTER_UP_HASH	  = text::hash("APP_POINTER_UP");
	const text::string_hash APP_POINTER_ZOOM	  = text::hash("APP_POINTER_ZOOM");

	const char* EVENT_TAG = "EVENT_TAG";

	std::atomic<bool> quitFlag = false;

	uiSys.addEventAction<polymorph::sys::event::Quit>
	(
		APP_EXIT_HASH,
		[&] { quitFlag = true; }
	);

	uiSys.addEventAction<polymorph::sys::event::Hide>
	(
		APP_HIDE_HASH,
		[&] { DEBUG_OUT(EVENT_TAG, "event::Hide"); }
	);

	uiSys.addEventAction<polymorph::sys::event::PointerDown>
	(
		APP_POINTER_DOWN_HASH,
		[&](const polymorph::sys::event::PointerDown& arg)
		{
			const gr::Vector2_r v2 = static_cast<const gr::Vector2_r&>(arg.pointerPos);
			DEBUG_OUT(EVENT_TAG, 
					  "event::PointerDown(%i, %i, {%f, %f})", 
					  arg.id, arg.button, 
					  v2[0], 
					  v2[1]);
		}
	);

	uiSys.addEventAction<polymorph::sys::event::PointerDrag>
	(
		APP_POINTER_DRAG_HASH,
		[&](const polymorph::sys::event::PointerDrag& arg)
		{
			DEBUG_OUT(EVENT_TAG, 
					  "event::PointerDrag(%i, %i, %i)",
					  arg.id, arg.dx, arg.dy);
		}
	);

	uiSys.addEventAction<polymorph::sys::event::PointerMove>
	(
		APP_POINTER_MOVE_HASH,
		[&](const polymorph::sys::event::PointerMove& arg)
		{
			DEBUG_OUT(EVENT_TAG,
					  "event::PointerMove(%i, %i, %i)",
					  arg.id, arg.dx, arg.dy);
		}
	);

	uiSys.addEventAction<polymorph::sys::event::PointerUp>
	(
		APP_POINTER_UP_HASH,
		[&](const polymorph::sys::event::PointerUp& arg)
		{
			const gr::Vector2_r v2 = static_cast<const gr::Vector2_r&>(arg.pointerPos);
			DEBUG_OUT(EVENT_TAG,
					  "event::PointerUp(%i, %i, {%f, %f})",
					  arg.id, arg.button, v2[0], v2[1]);
		}
	);

	uiSys.addEventAction<polymorph::sys::event::PointerZoom>
	(
		APP_POINTER_ZOOM,
		[&](const polymorph::sys::event::PointerZoom& arg)
		{
			DEBUG_OUT(EVENT_TAG, "event::PointerZoom(%i)", arg.dz);
		}
	);

	uiSys.waitForStartup();

	auto& grSys = uiSys.waitForGraphicsSystem();

	{
		auto transaction = grSys.sceneMutator();
		transaction.scene.addModel(TEST_MODEL_HASH, std::move(testModel));
	}

	uiSys.addEventAction<polymorph::sys::event::PointerDrag>
	(
		MOVE_MODEL_HASH,
		[&](const polymorph::sys::event::PointerDrag& arg)
		{
			auto transaction = grSys.sceneMutator();
			auto& model = transaction.scene.model(TEST_MODEL_HASH);

			DEBUG_OUT("MOVE_MODEL", "This is a drag!");
			
			model.transform() *= gr::Transform::translate(gr::real_t(arg.dx) * 0.001f, 0.0f);
			model.transform() *= gr::Transform::eulerAngle(gr::real_t(arg.dy) * 0.001f);
		}
	);

	uiSys.addEventAction<polymorph::sys::event::PointerUp>
	(
		SWAP_VSYNC_HASH,
		[&](const polymorph::sys::event::PointerUp& arg)
		{
			DEBUG_OUT("SWAP_VSYNC", "Toggling VSync.");
			grSys.actionQueue().pushAction
			(
				[&](polymorph::sys::GraphicsSystemRunner& runner)
				{
					runner.surface().setVSync(!lastSetVsync);
					lastSetVsync = !lastSetVsync;
				}
			);
		}
	);


	while ( !quitFlag )
	{

		polymorph::concurrency::Thread::sleep(TimeDuration::millis(60));
	}

	uiSys.removeEventAction<polymorph::sys::event::Quit>(APP_EXIT_HASH);

	uiSys.interrupt();
	uiSys.join();

	return 0;
}