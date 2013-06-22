#include "sys/UISystem.hpp"


namespace polymorph { namespace sys {

template <typename Event>
void UISystem::addEventAction(event_action_id id, const typename EventManager<Event>::ActionType& action)
{
	_actions.pushAction
	(
		[=](UISystemRunner& runner)
		{
			auto& actionMapping = runner.uiEvents().with<Event>().actionBindings();

			ASSERT(actionMapping.find(id) == actionMapping.end(),
				   "Trying to re-add action id.");

			actionMapping.insert(std::make_pair(id, std::move(action)));
		}
	);
}

template <typename Event>
void UISystem::removeEventAction(event_action_id id)
{
	_actions.pushAction
	(
		[=](UISystemRunner& runner)
		{
			auto& actionMapping = runner.uiEvents().with<Event>().actionBindings();

			ASSERT(actionMapping.find(id) != actionMapping.end(),
				   "Trying to remove non-exising action.");

			actionMapping.erase(id);
		}
	);
}

} }