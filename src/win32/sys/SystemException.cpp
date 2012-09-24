/**
 * @file SystemException.cpp
 * Win32 implementation of SystemException
 */

#include "NonCopyable.hpp"
#include "sys/SystemException.hpp"
#include <string>
#include <windows.h>

namespace sys {
namespace {

// for convenience
struct ScopedLocalFree : NonCopyable {
	ScopedLocalFree(HLOCAL p) : _p(p) {}
	~ScopedLocalFree() { LocalFree(_p); }
private:
	HLOCAL _p;
};

/**
 * A helper function for composing error messages associated with
 * Win32 error codes (from GetLastError()).
 */
text::String getWin32Message(DWORD error)
{
	LPVOID buffer = NULL;

	// NOTE: force call FormatMessageA so we can use a char buffer
	// instead of a TCHAR buffer and easily convert to text::String
	DWORD ret = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&buffer,
		0,
		NULL);

	if (ret == 0)
	{
		DWORD err = GetLastError();
		return "Unknown error";
	}

	ScopedLocalFree localfree(buffer);
	return text::String(static_cast<LPCSTR>(buffer));
}

}	// anonymous namespace


SystemException::SystemException(error_type code, const char* message) :
	Exception(message),
	_error(),	// lazy initialization in what()
	_code(code)
{
}

const char* SystemException::what() const
{
	if (_error.empty())
	{
		_error = Exception::what();
		if (!_error.empty()) _error.append(": ");
		_error.append(getWin32Message(_code));
	}

	return _error.c_str();
}

}	// namespace sys
