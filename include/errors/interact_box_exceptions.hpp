#pragma once
#include "errors.hpp"
#include "error_codes.hpp"

class InteractBoxException : public std::exception {
public:
	InteractBoxException(ErrorCodes::ErrorCode errCode, const std::string& msg) : message(msg), code(errCode) {}
	InteractBoxException(ErrorCodes::ErrorCode errCode, const std::wstring& msg) : message(StringHelper::wideStringToString(msg)), code(errCode) {}
	InteractBoxException(ErrorCodes::ErrorCode errCode) : code(errCode) {}
	InteractBoxException(ErrorCodes::ErrorCode errCode, DWORD windowsErrorCode) : message(std::to_string(windowsErrorCode)), code(errCode) {}

	std::string what();

private:
	std::string message = std::string();
	ErrorCodes::ErrorCode code;
	std::string windowsErrorCodeToString(DWORD windowsErrorCode);
};
