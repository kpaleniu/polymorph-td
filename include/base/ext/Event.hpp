

#ifndef EVENT_HPP_
#define EVENT_HPP_

#include "TemplateUtil.hpp"

#include <functional>
#include <list>

namespace detail
{
	struct ManagerType
	{
		template<typename Event>
		class type
		{
		public:
			typedef std::function<void (const Event&)> ActionType;

			void addAction(ActionType action)
			{
				_eventActions.push_back(action);
			}

			void triggerEvent(const Event& event)
			{
				for (auto& action : _eventActions)
					action(event);
			}

		private:
			std::list<ActionType> _eventActions;
		};
	};

	struct BindingType
	{
		template<typename Event>
		struct type
		{
			std::list<typename ManagerType::type<Event>::ActionType> actionBinding;
		};
	};
}

template<typename... Events>
using EventManager = InheritanceIterator<detail::ManagerType, Events...>;

template<typename... Events>
using ActionBindings = InheritanceIterator<detail::BindingType, Events...>;

#endif
