

#ifndef GUIMANAGER_HPP
#define GUIMANAGER_HPP

#include "gui/Page.hpp"

#include <sys/UISystem.hpp>
#include <sys/GraphicsSystem.hpp>

#include <gr/RenderPassManager.hpp>

#include <stack>

namespace gui {

/**
 * Game GUI managing class.
 *
 * This class is expected to live on the main thread. It manages
 * communications to the systems to set the GUI render pass and
 * event managing. It also holds a stack state to enable linear
 * page orientation.
 */
class GUIManager : NonCopyable
{
public:
	/**
	 * Creates the render pass (will block until added).
	 */
	GUIManager(sys::UISystem& uiSys, sys::GraphicsSystem& grSys);
	~GUIManager();

	void pushPage(Page&& page);
	void popPage();

private:
	void setPage(const Page& page);

	sys::UISystem& _uiSys;
	sys::GraphicsSystem& _grSys;

	std::stack<Page> _pages;
};

}


#endif
