#include <windows.h>

#include <sys/UISystem.hpp>
#include <text/util.hpp>

#include <sys/NTSystem.hpp>

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

const text::string_hash TEST_MESH_HASH = text::hash("TEST_MESH");

const char* EVENT_TAG = "EVENT_TAG";

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

class TestRunner
{
public:
	struct ConstructionArgs
	{
		polymorph::sys::UISystem&		uiSys;
		polymorph::sys::GraphicsSystem& grSys;
	};

	TestRunner(ConstructionArgs&& args, polymorph::sys::NTSystem<TestRunner>& system)
	:	_uiSys(args.uiSys), 
		_grSys(args.grSys),
		_meshManager(),
		_system(system)
	{
		_uiSys.waitForStartup();
		addUIListeners();

		_grSys.waitForStartup();
		addTestModelToScene();
	}

	TestRunner(TestRunner&& other)
	:	_uiSys(other._uiSys), 
		_grSys(other._grSys),
		_meshManager(std::move(other._meshManager)),
		_system(other._system)
	{
	}


	~TestRunner()
	{
		auto transaction = _grSys.sceneMutator();
		transaction.scene.removeModel(TEST_MODEL_HASH);
	}

	bool update(TimeDuration)
	{
		return true;
	}

private:
	void addTestModelToScene()
	{
		auto meshHandle = _meshManager.addMesh(TEST_MESH_HASH, std::move(createTestQuad()));

		std::vector<gr::Model::ModelMesh> meshes;
		gr::Model::ModelMesh modelMesh = {gr::Transform(), meshHandle};

		meshes.push_back(modelMesh);

		gr::Model testModel(std::move(meshes));

		{
			auto transaction = _grSys.sceneMutator();
			transaction.scene.addModel(TEST_MODEL_HASH, std::move(testModel));
		}
	}

	void addUIListeners()
	{
		_uiSys.addEventAction<polymorph::sys::event::Quit>
		(
			APP_EXIT_HASH,
			[this] 
			{ 
				_system.actionQueue().pushAction
				(
					[](TestRunner&)
					{
						polymorph::concurrency::Thread::interruptCurrent();
					}
				);
			}
		);

		_uiSys.addEventAction<polymorph::sys::event::Hide>
		(
			APP_HIDE_HASH,
			[&] { DEBUG_OUT(EVENT_TAG, "event::Hide"); }
		);

		_uiSys.addEventAction<polymorph::sys::event::PointerDrag>
		(
			APP_POINTER_DRAG_HASH,
			[this](const polymorph::sys::event::PointerDrag& arg)
			{
				_system.actionQueue().pushAction
				(
					[arg](TestRunner& thiz)
					{
						auto transaction = thiz._grSys.sceneMutator();
						auto& model = transaction.scene.model(TEST_MODEL_HASH);

						DEBUG_OUT("MOVE_MODEL", "This is a drag! (%i %i)", arg.dx, arg.dy);
						
						auto rotTrans = gr::Transform::eulerAngle(gr::real_t(arg.dy) * 0.001f);

						gr::Vector3_r worldPosDiff = { gr::real_t(arg.dx) * 0.001f, 0.0f, 0.0f };

						model.transform().translation() += worldPosDiff;
						model.transform() *= rotTrans;

						DEBUG_OUT("MOVE_MODEL",
								  "Pos: (%f %f)", 
								  model.transform().translation()[0], 
								  model.transform().translation()[1]);
					}
				);
			}
		);

	}

private:
	polymorph::sys::UISystem&		_uiSys;
	polymorph::sys::GraphicsSystem& _grSys;

	gr::MeshManager _meshManager;

	polymorph::sys::NTSystem<TestRunner>& _system;
};


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

	auto& grSys = uiSys.waitForGraphicsSystem();

	TestRunner::ConstructionArgs ctorArgs = {uiSys, grSys};

	{
		polymorph::sys::NTSystem<TestRunner> 
			mainSystem(TimeDuration::millis(10), 256, std::move(ctorArgs));

		mainSystem.enter();
	}
	
	uiSys.interrupt();
	uiSys.join();

	return 0;
}