
#include "pm_td/GameRunner.hpp"

#include <sys/UISystem.hpp>
#include <sys/NTSystem.hpp>

#include <windows.h>


int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE, LPSTR, int)
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

	pm_td::GameRunner::ConstructionArgs ctorArgs = { uiSys, grSys };

	{
		polymorph::sys::NTSystem<pm_td::GameRunner>
			mainSystem(TimeDuration::millis(10), 256, std::move(ctorArgs));

		mainSystem.enter();
	}

	uiSys.interrupt();
	uiSys.join();

	return 0;
}