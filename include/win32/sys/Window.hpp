/**
 * @file Window.hpp
 *
 */

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <gr/Surface.hpp>
#include <input/InputSource.hpp>
#include <input/WindowInputSource.hpp>
#include <os/MessageDialog.hpp>

#include <windows.h>

#include <memory>
#include <set>

namespace polymorph { namespace sys {
namespace detail {

/**
 * Custom deleter type to for HWND__ pointers.
 */
struct window_deleter
{
	void operator()(HWND window);
};

}

class Window : NonCopyable
{
public:
	struct Rect
	{
		int left;
		int top;
		int w;
		int h;
	};

	struct ConstructionData
	{
		HINSTANCE hInstance;
		Rect winRect;
	};

public:

	/**
	 *
	 */
	Window(const ConstructionData& desc);

	Window(Window&& window);
	/**
	 * Shows or hides the window.
	 * @return true if the window was visible previously
	 */
	bool show(bool show = true);

	void showMessageDialog(const std::string& title,
						   const std::string& message,
						   os::MessageDialog::Buttons buttons,
						   os::MessageDialog::Type type,
						   os::MessageDialog::Action action);

	/**
	 * Access to window input.
	 * @return	Reference to the input source active on this window.
	 */
	input::WindowInputSource& inputSource();

	gr::Surface& surface();

	/**
	 * @return A handle to the underlying native window
	 */
	HWND nativeHandle();

private:	// NOTE: surface has to be destroyed before the window

	struct DialogComp
	{
		bool operator()(const os::MessageDialog& lhs, const os::MessageDialog& rhs) const
		{
			return &lhs < &rhs;
		}
	};

	std::unique_ptr<HWND__, detail::window_deleter> _windowHandle;

	gr::Surface					_surface;
	input::WindowInputSource	_inputSource;
	std::set<os::MessageDialog, DialogComp>	_dialogs;
};

} }

#endif /* WINDOW_HPP_ */
