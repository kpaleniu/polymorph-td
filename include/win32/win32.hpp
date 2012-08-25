/**
 * @file win32.hpp
 *
 * Generic constructs used by win32 target.
 */

#ifndef WIN32_HPP_
#define WIN32_HPP_

#include <windows.h>

#include "gr/Window.hpp"

namespace gr {
struct Window::ConstructionData
{
	HINSTANCE hInstance;
	HINSTANCE hPrevInstance;
	LPSTR lpCmdLine;
	int nShowCmd;
};
}

#endif
