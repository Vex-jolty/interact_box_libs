#pragma once
#include "shared.hpp"
#include "errors/interact_box_exceptions.hpp"
#include "string_helper.hpp"
#include <windows.h>
#include <string>
#include <tlhelp32.h>
#include <tchar.h>
#include <boost/algorithm/string.hpp>

#if WINVER > _WIN32_WINNT_NT4
struct ProcessPathAndPID {
	std::wstring path;
	DWORD pid;
};

struct ANSIProcessPathAndPID {
	std::string path;
	DWORD pid;
};
#else
struct ProcessPathAndPID {
	std::string path;
	DWORD pid;
};
#endif

class ProcessHelper {
	public:
#if WINVER > _WIN32_WINNT_NT4
		static DWORD getProcessId(std::wstring path);
		static ANSIProcessPathAndPID getFirstProcessOfManyANSI(std::vector<std::string> paths);
		static ProcessPathAndPID getFirstProcessOfMany(std::vector<std::wstring> paths);
		static HWND findMainWindow(std::wstring path);
		static HWND findDisplaySettingsWindow();
		static void setToForeground(std::wstring path);
		static void killProcess(std::wstring path, int exitCode = 0);
		static BOOL CALLBACK enumDisplayWindows(HWND hwnd, LPARAM lParam);
#endif
		static DWORD getProcessId(std::string path);
		static ProcessPathAndPID getFirstProcessOfMany(std::vector<std::string> paths);
		static BOOL CALLBACK enumWindowsProc(HWND hwnd, LPARAM lParam);
		static HWND findMainWindow(DWORD processId);
		static HWND findMainWindow(std::string path);
		static void setToForeground(HWND hwnd);
		static void setToForeground(std::string path);
		static void killProcess(std::string path, int exitCode = 0);
		static void killProcess(DWORD pid, int exitCode = 0);
};