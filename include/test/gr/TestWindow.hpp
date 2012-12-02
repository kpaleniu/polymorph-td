
#ifndef TEST_BUILD
	#error "This file is only for test builds"
#endif

#ifndef TEST_WINDOW_HPP
#define TEST_WINDOW_HPP

#include "gr/Surface.hpp"

#include <windows.h>

void createTestWindow(HINSTANCE hinstance);
gr::Surface createSurface();
void destroyTestWindow();
bool updateTestWindow();

#endif
