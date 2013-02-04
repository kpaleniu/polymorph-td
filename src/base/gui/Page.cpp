#include "gui/Page.hpp"


namespace gui {

Page::Page(gr::SpriteSheet& sheet)
:	_widgets(),
 	_sheet(sheet)
{
}

Page::Page(Page&& other)
:	_widgets(std::move(other._widgets)),
 	_sheet(other._sheet)
{
}

void Page::attachToPass(gr::RenderPass& guiPass)
{
	guiPass.setTexture(&_sheet.texture());

	guiPass.clearVertexSuppliers();
	for (auto& widget : _widgets)
		guiPass.addVertexSupplier(widget);
}

}

