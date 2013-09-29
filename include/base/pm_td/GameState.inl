
#include "pm_td/GameState.hpp"

namespace polymorph { namespace pm_td {

inline GameState::GameState()
:	_impl(nullptr)
{
}

template <typename StateImpl>
GameState::GameState(StateImpl&& stateImpl)
:	_impl(std::unique_ptr<StateBase>(new StateDerived<StateImpl>(std::move(stateImpl))))
{
}

inline GameState::GameState(GameState && other)
:	_impl(std::move(other._impl))
{
}

inline void GameState::enterState()
{
	_impl->enterState();
}

inline void GameState::update(TimeDuration dt)
{
	_impl->update(dt);
}

inline void GameState::exitState()
{
	_impl->exitState();
}

inline GameState& GameState::operator=(GameState && other)
{
	_impl = std::move(other._impl);

	return *this;
}

inline GameState::operator bool() const
{
	return _impl != nullptr;
}


template <typename StateImpl>
GameState::StateDerived<StateImpl>::StateDerived(StateImpl&& stateImpl)
:	impl(std::move(stateImpl))
{
}

template <typename StateImpl>
void GameState::StateDerived<StateImpl>::enterState()
{
	impl.enterState();
}

template <typename StateImpl>
void GameState::StateDerived<StateImpl>::update(TimeDuration dt)
{
	impl.update(dt);
}

template <typename StateImpl>
void GameState::StateDerived<StateImpl>::exitState()
{
	impl.exitState();
}

} }