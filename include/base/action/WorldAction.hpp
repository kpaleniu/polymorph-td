/**
 * @file WorldAction.hpp
 *
 */

#ifndef WORLDACTION_HPP_
#define WORLDACTION_HPP_

#include "action/Action.hpp"
#include "sys/WorldSystem.hpp"

#include "Debug.hpp"

namespace action {
namespace world_action {

typedef Action<sys::WorldSystemRunner> WorldAction;

class TestAction : public WorldAction
{
public:
	struct Data
	{
		int i;
		int j;
	};

	void callAction(sys::WorldSystemRunner &runner, stream::AutoInputStream &in)
	{
		Data data;
		in >> data;
		action(data.i, data.j);
	}

	void action(int i, int j)
	{
		DEBUG_OUT("Action! " << i << " " << j);
	}

} TestAction;

}
}

#endif /* WORLDACTION_HPP_ */
