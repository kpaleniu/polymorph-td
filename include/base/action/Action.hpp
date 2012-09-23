/**
 * @file Action.hpp
 *
 */

#ifndef ACTION_HPP_
#define ACTION_HPP_


namespace stream {
	class AutoInputStream;
}

namespace action {

template<typename SystemRunner>
class Action
{
public:
	virtual ~Action()
	{
	}

	virtual void callAction(SystemRunner &, stream::AutoInputStream &) = 0;
};

}


#endif /* ACTION_HPP_ */
