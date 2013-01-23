

#ifndef EVENT_HPP_
#define EVENT_HPP_

#include <NonCopyable.hpp>

#include <functional>
#include <list>

template<typename... Events>
class EventManager;

template<typename Event, typename... Events>
class EventManager<Event, Events...> : public EventManager<Events...>
{
public:
	typedef std::function<void (const Event&)> ActionType;

	using EventManager<Events...>::addAction;
	using EventManager<Events...>::triggerEvent;


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

template<typename Event>
class EventManager<Event> : NonCopyable
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


/*
template <typename... Args> class TESTCOUNT;

template <typename T, typename... Args>
class TESTCOUNT<T, Args...> : public TESTCOUNT<Args...>
{
};

template <> class TESTCOUNT<> {};
*/

#endif
