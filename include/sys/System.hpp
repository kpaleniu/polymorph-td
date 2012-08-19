/**
 * @file System.hpp
 *
 */

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "sys/time.hpp"
#include "sys/Thread.hpp"

namespace sys
{
	class System : private Thread
	{
	public:
		System(time_t sync);
		virtual ~System();

		/**
		 * Starts the system.
		 */
		void start();
		/**
		 * Pauses the system.
		 */
		void pause();
		/**
		 * Un-pauses the system.
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
		const time_t _sync;

	private:
		virtual void threadMain();
	};
}


#endif /* SYSTEM_HPP_ */
