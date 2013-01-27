

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

			void triggerEvent(const Event& event)
			{
				for (auto& action : _eventActions)
					action(event);
			}

			std::list<ActionType>& actionBindings()
			{ return _eventActions; }

			const std::list<ActionType>& actionBindings() const
			{ return _eventActions; }

		private:
			std::list<ActionType> _eventActions;
		};
	};
}

template<typename Event>
using ManagerFor = detail::ManagerType::type<Event>;

template<typename... Events>
class EventManager : public InheritanceIterator<detail::ManagerType, Events...>
{
public:
	template<typename Event>
	ManagerFor<Event>& with()
	{ return *static_cast<ManagerFor<Event>*>(this); }

	template<typename Event>
	const ManagerFor<Event>& with() const
	{ return *static_cast<const ManagerFor<Event>*>(this); }
};



#endif
