#ifndef WIDGET_HPP_
#define WIDGET_HPP_

#include <gr/Sprite.hpp>

namespace gui {

class Widget : public gr::Sprite
{
public:
	Widget(const gr::Sprite& sprite, std::function<void ()> clickAction);


private:
	std::function<void ()> _clickAction;

};

}


#endif
