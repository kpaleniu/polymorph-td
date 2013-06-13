#include <windows.h>

#include <sys/UISystem.hpp>
#include <text/util.hpp>


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE, LPSTR , int)
{
	polymorph::sys::Window::ConstructionData winCtorData;

	winCtorData.hInstance = hInstance;
	winCtorData.winRect.left = 256;
	winCtorData.winRect.top = 256;
	winCtorData.winRect.w = 800;
	winCtorData.winRect.h = 600;

	polymorph::sys::UISystem uiSys(winCtorData);
	uiSys.start();
	uiSys.waitForStartup();

	text::string_hash APP_EXIT_HASH = text::hash("APP_EXIT");

	std::atomic<bool> quitFlag = false;

	uiSys.actionQueue().pushAction(
	[&](polymorph::sys::UISystemRunner& runner) 
	{ 
		auto& actionMapping = runner.uiEvents().with<polymorph::sys::event::Quit>().actionBindings();
		actionMapping[APP_EXIT_HASH] = 
		[&] 
		{ 
			quitFlag = true; 
		};
	});

	while ( !quitFlag )
	{

		polymorph::concurrency::Thread::sleep(TimeDuration::millis(60));
	}

	uiSys.interrupt();
	uiSys.join();

	return 0;
}