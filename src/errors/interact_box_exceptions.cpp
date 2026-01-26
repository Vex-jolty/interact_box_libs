#include "errors/interact_box_exceptions.hpp"

std::string InteractBoxException::what() {
	std::string codeMessage = getErrorMessage(code);
	if (message.empty())
		return codeMessage;
	return codeMessage + " " + message;
}

#ifdef WIN32
std::string InteractBoxException::windowsErrorCodeToString(DWORD windowsErrorCode) {
	if (windowsErrorCode == 0)
		return std::string();
	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, windowsErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0,
		NULL
	);
	std::string message(messageBuffer, size);
	LocalFree(messageBuffer);
	return message;
}
#endif
