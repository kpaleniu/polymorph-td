#pragma once

#include <Time.hpp>

#include <NonCopyable.hpp>

#include <memory>

namespace polymorph { namespace pm_td {

class GameRunner;

class GameState : NonCopyable
{
public:
	/** Constructs an empty state, a "null object". */
	GameState();

	template <typename StateImpl>
	GameState(StateImpl&& stateImpl);

	GameState(GameState&& other);


	GameState& operator=(GameState&& other);

	/** Checks if state is empty. */
	operator bool() const;

	void enterState();
	void update(TimeDuration dt);
	void exitState();

private:

	struct StateBase
	{
		virtual ~StateBase() {};
		virtual void enterState() = 0;
		virtual void update(TimeDuration dt) = 0;
		virtual void exitState() = 0;
	};

	template <typename StateImpl>
	struct StateDerived : ::NonCopyable, StateBase
	{
		StateDerived(StateImpl&& stateImpl);

		void enterState() override;
		void update(TimeDuration dt) override;
		void exitState() override;

		StateImpl impl;
	};

	std::unique_ptr<StateBase> _impl;
};


} }

#include "pm_td/GameState.inl"
