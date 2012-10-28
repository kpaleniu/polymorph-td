/**
 * @file win_main.cpp
 *
 * Holds the definition of the main function for Windows OS.
 */

#include <sys/GraphicsSystem.hpp>
#include <sys/UISystem.hpp>

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


	std::vector<gr::VertexBuffer> buffers;

	uiSystem.graphicsAccess().actionQueue().pushAction(
	[&buffers](sys::GraphicsSystemRunner& grSys)
	{
		gr::real vecs[] = {-.5f, -.5f,
						    .5f, -.5f,
						    .5f,  .5f,
						   -.5f,  .5f};

		//grSys.renderer().debugDraw().drawLine2D(0.0f, 0.0f, 1.0f, 1.0f);
		buffers.push_back(
			grSys.renderer().
				bufferManager().
					createVertexBuffer(gr::VertexFormat::V2,
					                   gr::BufferUsage::STATIC,
					                   4, vecs));

		//buffers.back().writeVertices(0, 4, vecs);

		buffers.back().draw(gr::Primitive::QUADS);
		buffers.clear();
	});

	uiSystem.join();

	DEBUG_OUT(TAG, "UI system is shut down");

	profiler::ThreadProfiler::dumpAll(std::cout);
	profiler::ThreadProfiler::shutdown();
	text::clearInterned();


	return 0;
}
