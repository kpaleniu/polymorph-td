/**
 * @file win_main.cpp
 * 
 * Holds the definition of the main function for Windows OS.
 */

#include <sys/WorldSystem.hpp>

#include "win32.hpp"

#include <iostream>
using namespace std;

/*
 * struct Window::ConstructionData
 {
 HINSTANCE hInstance;
 HINSTANCE hPrevInstance;
 LPSTR lpCmdLine;
 int nShowCmd;
 };
 */

/**
 * Windows main.
 */
int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpCmdLine,
					 int nShowCmd)
{
	cout << "Hello World!" << endl;

	gr::Window::ConstructionData winData = { hInstance,
											 hPrevInstance,
											 lpCmdLine,
											 nShowCmd };

	sys::WorldSystem worldSystem(winData);

	return 0;
}
