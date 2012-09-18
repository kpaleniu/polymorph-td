/**
 * @file Action.hpp
 *
 */

#ifndef ACTION_HPP_
#define ACTION_HPP_

namespace action {

class Action
{
public:
	virtual ~Action()
	{
	}

	virtual void callAction(stream::AutoInputStream &) = 0;
};

}


#endif /* ACTION_HPP_ */
