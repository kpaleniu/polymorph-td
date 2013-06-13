#include "os/MessageDialog.hpp"

#include <text/util.hpp>
#include <Assert.hpp>

namespace polymorph { namespace os {

MessageDialog::MessageDialog(const std::string& title, 
							 const std::string& message, 
							 Buttons buttons, 
							 Type type,
							 Action action,
							 HWND parent)
:	concurrency::Thread(),
	_title(title),
	_message(message),
	_buttons(buttons),
	_type(type),
	_action(action),
	_parent(parent)
{
}

MessageDialog::MessageDialog(MessageDialog&& other)
:	concurrency::Thread(std::move(other)),
	_title(std::move(other._title)),
	_message(std::move(other._message)),
	_buttons(other._buttons),
	_type(other._type),
	_action(std::move(other._action)),
	_parent(other._parent)
{
}

MessageDialog::~MessageDialog()
{
	join();
}

bool MessageDialog::isFinished() const
{
	return getThreadState() == ThreadState::EXITED;
}

void MessageDialog::show()
{
	start();
}

void MessageDialog::threadMain()
{
	int resp = MessageBox( _parent,
						   _message.c_str(),
						   _title.c_str(),
						   long(_type) | long(_buttons) );

	UserResponse userResp = UserResponse(resp);

#ifdef _DEBUG
	switch (userResp)
	{
		case UserResponse::RESP_ABORT:
		case UserResponse::RESP_CANCEL:
		case UserResponse::RESP_IGNORE:
		case UserResponse::RESP_NO:
		case UserResponse::RESP_OK:
		case UserResponse::RESP_RETRY:
		case UserResponse::RESP_TRYAGAIN:
		case UserResponse::RESP_YES:
			break;
		default:
			ASSERT(false, "Illegal response from MessageBox.");
	}
#endif

	if (_action)
		_action(userResp);
}

} }


