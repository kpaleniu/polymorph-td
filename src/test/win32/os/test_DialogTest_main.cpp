
#include "os/MessageDialog.hpp"
#include <Debug.hpp>

#include <windows.h>

#include <iostream>

/**
 * Windows main.
 */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE, LPSTR, int)
{
	os::MessageDialog::Action action = 
	[](os::MessageDialog::UserResponse resp)
	{
		DEBUG_OUT("TEST", "Got response");
	};

	os::MessageDialog dialog1("TEST1",
							  "Test Message",
							  os::MessageDialog::Buttons::BUTTON_OK,
							  os::MessageDialog::Type::TYPE_QUESTION,
							  action);


	return 0;
}
