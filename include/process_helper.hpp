#pragma once
#include "shared.hpp"
#include "errors/interact_box_exceptions.hpp"
#include "string_helper.hpp"
#include <string>
#ifdef WIN32
	#include <windows.h>
	#include <tlhelp32.h>
	#include <tchar.h>
#else
	#include <dirent.h>
	#include <unistd.h>
	#include <limits.h>
	#include <fstream>
	#include <filesystem>
	#include <signal.h>
#endif
#include <boost/algorithm/string.hpp>

#if defined(WIN32) && WINVER > _WIN32_WINNT_NT4
struct ProcessPathAndPID {
		std::wstring path;
		DWORD pid;
};

struct ANSIProcessPathAndPID {
		std::string path;
		DWORD pid;
};
#elif defined(WIN32)
struct ProcessPathAndPID {
		std::string path;
		DWORD pid;
};
#else

struct ProcessPathAndPID {
		std::string path;
		int pid;
};
#endif

class ProcessHelper {
	public:
#ifdef WIN32
	#if WINVER > _WIN32_WINNT_NT4
		static DWORD getProcessId(const std::wstring& path);
		static ANSIProcessPathAndPID getFirstProcessOfManyANSI(std::vector<std::string> paths);
		static ProcessPathAndPID getFirstProcessOfMany(std::vector<std::wstring> paths);
		static HWND findMainWindow(const std::wstring& path);
		static HWND findDisplaySettingsWindow();
		static void setToForeground(const std::wstring& path);
		static void killProcess(const std::wstring& path, int exitCode = 0);
		static BOOL CALLBACK enumDisplayWindows(HWND hwnd, LPARAM lParam);
	#endif
		static DWORD getProcessId(const std::string& path);
		static ProcessPathAndPID getFirstProcessOfMany(std::vector<std::string> paths);
		static BOOL CALLBACK enumWindowsProc(HWND hwnd, LPARAM lParam);
		static HWND findMainWindow(DWORD processId);
		static HWND findMainWindow(const std::string& path);
		static void setToForeground(HWND hwnd);
		static void setToForeground(const std::string& path);
		static void killProcess(const std::string& path, int exitCode = 0);
		static void killProcess(DWORD pid, int exitCode = 0);
#else
		static pid_t getProcessId(const std::string& name);
		static ProcessPathAndPID getFirstProcessOfMany(std::vector<std::string> names);
		static void killProcess(const std::string& name);
		static void killProcess(pid_t pid);
#endif
};