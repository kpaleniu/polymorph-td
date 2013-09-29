
#include "pm_td/GameRunner.hpp"

#include <sys/Systems.hpp>

#include <windows.h>


int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE, LPSTR, int)
{
	using namespace polymorph::sys;

	Window::ConstructionData winCtorData;

	winCtorData.hInstance = hInstance;
	winCtorData.winRect.left = 256;
	winCtorData.winRect.top = 256;
	winCtorData.winRect.w = 800;
	winCtorData.winRect.h = 600;

	Systems::startUp(std::move(winCtorData));

	{
		polymorph::sys::NTSystem<polymorph::pm_td::GameRunner>
			mainSystem(TimeDuration::millis(10), 256, {});

		mainSystem.enter();
	}

	Systems::tearDown();

	return 0;
}