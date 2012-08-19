/**
 * @file win_main.cpp
 * 
 * Holds the definition of the main function for Windows OS.
 */

#include <windows.h>

#include <iostream>
using namespace std;

/**
 * Windows main.
 */
int APIENTRY WinMain(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR lpCmdLine,
		int nShowCmd)
{
	cout << "Hello World!" << endl;

	return 0;
}
