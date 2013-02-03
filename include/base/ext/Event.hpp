

#ifndef EVENT_HPP_
#define EVENT_HPP_

#include <functional>
#include <list>

namespace detail {

template<typename Event, typename ActionType>
class ManagerBase
{
public:
	std::list<ActionType>& actionBindings()
	{ return _eventActions; }

	const std::list<ActionType>& actionBindings() const
	{ return _eventActions; }
protected:
	std::list<ActionType> _eventActions;
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
			action(param);
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
			action();
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
