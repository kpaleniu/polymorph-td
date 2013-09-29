

#ifndef EVENT_HPP_
#define EVENT_HPP_

#include <type_traits>
#include <functional>
#include <map>


typedef std::size_t event_action_id;

namespace detail {

template<typename Event, typename ActionType>
class ManagerBase
{
public:
	std::map<event_action_id, ActionType>& actionBindings()
	{ return _eventActions; }

	const std::map<event_action_id, ActionType>& actionBindings() const
	{ return _eventActions; }
protected:
	std::map<event_action_id, ActionType> _eventActions;
};

}

template<typename Event, bool EmptyParam = std::is_empty<Event>::value>
class EventManager : public detail::ManagerBase<Event, std::function<void (const Event&)>>
{
public:
	typedef typename std::function<void (const Event&)> ActionType;

	void triggerEvent(const Event& param)
	{
		for (auto& action : detail::ManagerBase<Event, ActionType>::_eventActions)
			action.second(param);
	}
};

template<typename Event>
class EventManager<Event, true> : public detail::ManagerBase<Event, std::function<void ()>>
{
public:
	typedef typename std::function<void ()> ActionType;

	void triggerEvent()
	{
		for (auto& action : detail::ManagerBase<Event, ActionType>::_eventActions)
			action.second();
	}
};

template<typename... Events>
class EventManagers : public EventManager<Events>...
{
public:
	template<typename Event>
	EventManager<Event>& with()
	{ return *static_cast<EventManager<Event>*>(this); }

	template<typename Event>
	const EventManager<Event>& with() const
	{ return *static_cast<const EventManager<Event>*>(this); }
};


#endif
