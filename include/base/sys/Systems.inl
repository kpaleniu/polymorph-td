
#include "sys/Systems.hpp"

namespace polymorph { namespace sys {

template <>
UISystem& Systems::system()
{
	return _instance->_uiSys;
}

template <>
GraphicsSystem& Systems::system()
{
	return *_instance->_grSys;
}

template <typename SystemType, typename... SystemTypes>
void Systems::queue(typename polymorph::sys::SystemActionQueue<typename SystemType::Runner>::RunnerAction action,
					typename polymorph::sys::SystemActionQueue<typename SystemTypes::Runner>::RunnerAction... post)
{
	system<SystemType>().actionQueue().pushAction
	(
		[=](typename SystemType::Runner& runner)
		{
			action(runner);
			queue(post);
		}
	);
}

template <typename SystemType>
void Systems::queue(typename polymorph::sys::SystemActionQueue<typename SystemType::Runner>::RunnerAction action)
{
	system<SystemType>().actionQueue().pushAction(action);
}

} }