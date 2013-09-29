#include "sys/Systems.hpp"

#include <Assert.hpp>

namespace polymorph { namespace sys {

std::unique_ptr<Systems> Systems::_instance = nullptr;

void Systems::startUp(UISystemRunner::ConstructionArgs&& uiArgs)
{
	ASSERT(_instance == nullptr, "Systems have already been started.");

	_instance = std::unique_ptr<Systems>(new Systems(std::move(uiArgs)));
}

void Systems::tearDown()
{
	ASSERT(_instance != nullptr, "Systems have not been started.");

	_instance = nullptr;
}


Systems::Systems(UISystemRunner::ConstructionArgs&& uiArgs)
:	_uiSys(std::move(uiArgs)), 
	_grSys(nullptr)
{
	_uiSys.start();
	_grSys = &_uiSys.waitForGraphicsSystem();
}

Systems::~Systems()
{
	_uiSys.interrupt();
	_uiSys.join();
}

} }