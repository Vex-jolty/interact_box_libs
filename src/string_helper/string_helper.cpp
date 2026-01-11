#include "string_helper.hpp"

using namespace std;
string StringHelper::removePrefix(const string& str, const string& prefix) {
	if (str.size() >= prefix.size() &&
			str.compare(0, prefix.size(), prefix) == 0) {
		return str.substr(prefix.size());
	}
	return str;
}

string StringHelper::removeSuffix(const string& str, const string& suffix) {
	if (str.size() >= suffix.size() &&
			str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0) {
		return str.substr(0, str.size() - suffix.size());
	}
	return str;
}

wstring StringHelper::removePrefix(const wstring& str, const wstring& prefix) {
	if (str.size() >= prefix.size() &&
			str.compare(0, prefix.size(), prefix) == 0) {
		return str.substr(prefix.size());
	}
	return str;
}

wstring StringHelper::removeSuffix(const wstring& str, const wstring& suffix) {
	if (str.size() >= suffix.size() &&
			str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0) {
		return str.substr(0, str.size() - suffix.size());
	}
	return str;
}


string StringHelper::toLowercase(string input) {
	string lowerStr = input;
	transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
		[](unsigned char c) { return tolower(c); });
	return lowerStr;
}

wstring StringHelper::toLowercase(wstring input) {
	wstring lowerStr = input;
	transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
		[](unsigned char c) { return tolower(c); });
	return lowerStr;
}

wstring StringHelper::stringToWideString(string input) {
	int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, input.c_str(), (int)input.size(), NULL, 0);
	wstring wstr(sizeNeeded, 0);
	MultiByteToWideChar(CP_UTF8, 0, input.c_str(), (int)input.size(), &wstr[0], sizeNeeded);
	return wstr;
}

string StringHelper::wideStringToString(wstring input) {
	int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, &input[0], (int)input.size(), NULL, 0, NULL, NULL);
	string str(sizeNeeded, 0);
	WideCharToMultiByte(CP_UTF8, 0, &input[0], (int)input.size(), &str[0], sizeNeeded, NULL, NULL);
	return str;
}

vector<string> StringHelper::splitString(string input, string separator) {
	vector<string> result;
	string token;
	size_t pos = input.find(separator);
	do {
		token = input.substr(0, pos);
		result.push_back(token);
		input.erase(0, pos + separator.size());
	} while ((pos = input.find(separator)) != string::npos);
	result.push_back(input);
	return result;
}

vector<wstring> StringHelper::splitString(wstring input, wstring separator) {
	vector<wstring> result;
	wstring token;
	size_t pos = input.find(separator);
	if (pos != wstring::npos) {
		do {
			token = input.substr(0, pos);
			result.push_back(token);
			input.erase(0, pos + separator.size());
		} while ((pos = input.find(separator)) != wstring::npos);
	}
	result.push_back(input);
	return result;
}

string StringHelper::camelCaseToHuman(string input, bool capitalizeFirstLetter) {
	string output;
	for (int i = 0; i < input.size(); i++) {
		char c = input[i];
		if (!isupper(c) || isupper(input[i - 1]) || i != input.size() - 1 && isupper(input[i + 1])) {
			output += c;
		} else {
			output += ' ';
			output += tolower(c);
		}
	}
	if (capitalizeFirstLetter) output[0] = toupper(output[0]);
	return output;
}

#if WINVER > _WIN32_WINNT_NT4
wstring StringHelper::getWideStringFromLibrary(wstring libraryName, int stringId) {
  HMODULE libraryHandle = LoadLibrary(libraryName.c_str());
	if (!libraryHandle) throw runtime_error("cannot load library " + wideStringToString(libraryName.c_str()));
	wchar_t buffer[256];
	int length = LoadString(libraryHandle, stringId, buffer, 256);
	FreeLibrary(libraryHandle);
	return wstring(buffer);
}
#endif