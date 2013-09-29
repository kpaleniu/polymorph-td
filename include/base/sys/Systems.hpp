#ifndef SYS_SYSTEMS_HPP_
#define SYS_SYSTEMS_HPP_

#include "sys/GraphicsSystem.hpp"
#include "sys/UISystem.hpp"
#include "sys/SystemActionQueue.hpp"

#include <functional>
#include <memory>

namespace polymorph { namespace sys {

class Systems
{
public:
	static void startUp(UISystemRunner::ConstructionArgs&& uiArgs);
	static void tearDown();

	template <typename SystemType>
	static SystemType& system();

	template <>
	static UISystem& system();

	template <>
	static GraphicsSystem& system();

	template <typename... SystemTypes>
	static void queue(typename polymorph::sys::SystemActionQueue<typename SystemTypes::Runner>::RunnerAction... actions);

	template <typename SystemType, typename... SystemTypes>
	static void queue(typename SystemActionQueue<typename SystemType::Runner>::RunnerAction action,
					  typename SystemActionQueue<typename SystemTypes::Runner>::RunnerAction... post);

	template <typename SystemType>
	static void queue(typename SystemActionQueue<typename SystemType::Runner>::RunnerAction action);

	~Systems();

private:
	Systems(UISystemRunner::ConstructionArgs&& uiArgs);

	static std::unique_ptr<Systems> _instance;

	UISystem _uiSys;
	GraphicsSystem* _grSys;
};

} }

#include "sys/Systems.inl"

#endif