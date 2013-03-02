#ifndef MESSAGE_DIALOG_HPP_
#define MESSAGE_DIALOG_HPP_

#include <concurrency/Thread.hpp>

#include <windows.h>
#include <functional>

namespace os {

/**
 * Non-blocking message dialog.
 */
class MessageDialog : private concurrency::Thread
{
public:
	enum class Buttons : long
	{
		BUTTON_OK			= MB_OK,
		BUTTON_RETRY_CANCEL	= MB_RETRYCANCEL,
		BUTTON_YES_NO		= MB_YESNO
	};

	enum class Type : long
	{
		TYPE_WARNING	= MB_ICONWARNING,
		TYPE_ERROR		= MB_ICONERROR,
		TYPE_QUESTION	= MB_ICONQUESTION,
		TYPE_INFO		= MB_ICONINFORMATION
	};

	enum class UserResponse : int
	{
		RESP_ABORT		= IDABORT,
		RESP_CANCEL		= IDCANCEL,
		RESP_IGNORE		= IDIGNORE,
		RESP_NO			= IDNO,
		RESP_OK			= IDOK,
		RESP_RETRY		= IDRETRY,
		RESP_TRYAGAIN	= IDTRYAGAIN,
		RESP_YES		= IDYES
	};

	typedef std::function<void (UserResponse)> Action;

	MessageDialog(const std::string& title, 
				  const std::string& message, 
				  Buttons buttons, 
				  Type type,
				  Action action,
				  HWND parent = NULL);

	MessageDialog(MessageDialog&& other);

	~MessageDialog();

	bool isFinished() const;

protected:
	void threadMain();

private:
	const std::string	_title;
	const std::string	_message;

	const Buttons		_buttons;
	const Type			_type;
	const Action		_action;
	const HWND			_parent;
};

}




#endif