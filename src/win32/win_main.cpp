/**
 * @file win_main.cpp
 *
 * Holds the definition of the main function for Windows OS.
 */

#include <sys/GraphicsSystem.hpp>
#include <sys/UISystem.hpp>

#include <game/World.hpp>

#include <Debug.hpp>

#include <input/InputSource.hpp>

#include <vector>

// print tag
namespace { const char* TAG = "Main"; }

class TestSurfaceListener : public input::SurfaceListener
{
public:
	TestSurfaceListener()
	{
	}

	virtual void onResize(int w, int h)
	{

	}
	virtual void onShow()
	{

	}
	virtual void onHide()
	{

	}
	virtual void onQuit()
	{
		concurrency::Thread::interruptCurrent();
	}
};


/**
 * Windows main.
 */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE,
                     LPSTR /*lpCmdLine*/,
                     int /*nShowCmd*/)
{
	DEBUG_OUT(TAG, "Hello World!");

	sys::Window::ConstructionData winData = { hInstance,
	                                          { 64,
	                                            64,
	                                            800,
	                                            600 } };

	sys::UISystem uiSystem(winData);
	uiSystem.start();

	uiSystem.waitForStartup();

	uiSystem.actionQueue().pushAction(
	[](sys::UISystemRunner& uiRunner)
	{
		DEBUG_OUT("ACTION", "TEST");
	});

	TestSurfaceListener testListener;

	uiSystem.actionQueue().pushAction(
	[&](sys::UISystemRunner& uiRunner)
	{
		uiRunner.window().inputSource().setSurfaceListener(&testListener);
	});


	//std::vector<gr::VertexBuffer> buffers;

	uiSystem.graphicsAccess().actionQueue().pushAction(
	[&](sys::GraphicsSystemRunner& grSys)
	{
		grSys.renderer().addRenderAction(
		[](gr::Renderer& renderer) -> bool
		{
			renderer.debugDraw().drawLine2D(0.0f, 0.0f, 1.0f, 1.0f);
			return true;
		});

	});

	DEBUG_OUT(TAG, "Creating world");
	game::World myWorld;
	text::string_hash enemy1, enemy2, tower1, target, hp, position;

	enemy1 = text::intern("enemy1");
	enemy2 = text::intern("enemy2");
	tower1 = text::intern("tower1");

	position = text::intern("position");

	target = text::intern("target");
	hp = text::intern("hp");

	auto e1 = myWorld.entityManager.addEntity(enemy1);
	auto e2 = myWorld.entityManager.addEntity(enemy2);
	auto t1 = myWorld.entityManager.addEntity(tower1);

	e1.addComponent(position).insert({1.5f, 1.2f});
	e1.addComponent(hp).insert(100);

	e2.addComponent(position).insert({1.1f, 0.2f});
	e2.addComponent(hp).insert(75);

	t1.addComponent(position).insert({1.0f, 1.0f});
	t1.addComponent(target).insert(size_t(enemy1));

	DEBUG_OUT(TAG, "Flipping buffers");
	myWorld.entityManager.flipBuffers();

	while ( uiSystem.getThreadState() != concurrency::Thread::ThreadState::EXITED)
	{
		// Should not be needed to reassign each iteration...
		size_t theTarget = myWorld.entityManager.findEntity(tower1).findReader(target).read().asSize();
		auto targetHpWriter = myWorld.entityManager.findEntity(theTarget).findWriter(hp);
		auto targetHpReader = myWorld.entityManager.findEntity(theTarget).findReader(hp);
		//

		if (targetHpReader.read().asInt() <= 0)
			break;

		targetHpWriter.write(targetHpReader.read().asInt() - 2);

		DEBUG_OUT(TAG, "HP: %i", targetHpReader.read().asInt());

		myWorld.entityManager.flipBuffers();
		concurrency::Thread::sleep(sys::TimeDuration::millis(1000));
	}


	uiSystem.interrupt();
	uiSystem.join();

	DEBUG_OUT(TAG, "UI system is shut down");

	profiler::ThreadProfiler::dumpAll(std::cout);
	profiler::ThreadProfiler::shutdown();
	text::clearInterned();


	return 0;
}
