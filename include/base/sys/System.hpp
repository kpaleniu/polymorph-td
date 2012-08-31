/**
 * @file System.hpp
 *
 * Interface for systems.
 */

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "sys/Time.hpp"
#include "sys/Thread.hpp"

namespace sys
{
	/**
	 * Abstract base class for systems.
	 */
	class System : private Thread
	{
	public:
		System(const TimeDuration &sync);
		virtual ~System();

		/**
		 * Starts the system.
		 */
		void start();
		/**
		 * Pauses the system.
		 * If the system is already paused the
		 * method returns without any actions.
		 */
		void pause();
		/**
		 * Resumes the system.
		 * If the system is already running the
		 * method returns without any actions.
		 */
		void resume();
		/**
		 * Stops the system.
		 * Once stopped the system cannot be resumed.
		 */
		void stop();

	protected:
		/**
		 * System update method.
		 */
		virtual void update() = 0;

	protected:
		const TimeDuration _sync;

	private:
		virtual void threadMain();
	};
}

#endif /* SYSTEM_HPP_ */
