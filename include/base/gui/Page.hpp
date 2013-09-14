#ifndef PAGE_HPP_
#define PAGE_HPP_

#include "gui/Widget.hpp"

#include <gr/SpriteSheet.hpp>
#include <gr/RenderPass.hpp>

#include <NonCopyable.hpp>

#include <list>

namespace gui {

class Page
{
public:
	Page(gr::SpriteSheet& sheet);
	Page(Page&& other);

	Page(const Page& other) = default;

	/**
	 * Sets the sprite sheet and widgets to the render pass.
	 */
	void attachToPass(gr::RenderPass& guiPass);

	//void addWidget(Widget&& widget);

private:
	std::list<Widget> _widgets;

	gr::SpriteSheet& _sheet;
};

}


#endif
