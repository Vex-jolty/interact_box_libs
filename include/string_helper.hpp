#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include <algorithm>
#include "shared.hpp"
#include <stdexcept>

class StringHelper {
	public:
		static std::string removePrefix(const std::string& str, const std::string& prefix);
		static std::wstring removePrefix(const std::wstring& str, const std::wstring& prefix);
		static std::string removeSuffix(const std::string& str, const std::string& suffix);
		static std::wstring removeSuffix(const std::wstring& str, const std::wstring& suffix);
		static std::string toLowercase(std::string input);
		static std::wstring toLowercase(std::wstring input);
		static std::wstring stringToWideString(std::string input);
		static std::string wideStringToString(std::wstring input);
		static std::vector<std::string> splitString(std::string input, std::string separator);
		static std::vector<std::wstring> splitString(std::wstring input, std::wstring separator);
		static std::string camelCaseToHuman(std::string input, bool capitalizeFirstLetter = false);
		#if WINVER > _WIN32_WINNT_NT4
		static std::wstring getWideStringFromLibrary(std::wstring libraryName, int stringId);
		#endif
};