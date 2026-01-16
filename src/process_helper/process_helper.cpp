#include "process_helper.hpp"

using namespace std;

#if WINVER > _WIN32_WINNT_NT4
DWORD ProcessHelper::getProcessId(wstring path) {
	DWORD processId = 0;
	PROCESSENTRY32W entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (Process32First(snapshot, &entry)) {
		do {
			if (_tcsicmp(entry.szExeFile, (path.c_str())) == 0) {
				processId = entry.th32ProcessID;
				break;
			}
		} while (Process32Next(snapshot, &entry));
	}
	CloseHandle(snapshot);
	return processId;
}
#endif

DWORD ProcessHelper::getProcessId(string path) {
	DWORD processId = 0;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (Process32First(snapshot, &entry)) {
		do {
#if WINVER > _WIN32_WINNT_NT4
			if (_tcsicmp(entry.szExeFile, StringHelper::stringToWideString(path).c_str()) == 0) {
				processId = entry.th32ProcessID;
				break;
			}
#else
			if (_tcsicmp(entry.szExeFile, (path.c_str())) == 0) {
				processId = entry.th32ProcessID;
				break;
			}
#endif
		} while (Process32Next(snapshot, &entry));
	}
	CloseHandle(snapshot);
	return processId;
}

#if WINVER > _WIN32_WINNT_NT4
ProcessPathAndPID ProcessHelper::getFirstProcessOfMany(vector<string> paths) {
	ProcessPathAndPID processPathAndPID = {L"", 0};
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (Process32First(snapshot, &entry)) {
		do {
			for (auto &path : paths) {
				wstring widePath = StringHelper::stringToWideString(path);
				if (_tcsicmp(entry.szExeFile, StringHelper::stringToWideString(path).c_str()) == 0) {
					processPathAndPID.pid = entry.th32ProcessID;
					processPathAndPID.path = widePath;
					CloseHandle(snapshot);
					return processPathAndPID;
				}
			}
		} while (Process32Next(snapshot, &entry));
	}
	CloseHandle(snapshot);
	return processPathAndPID;
}

ANSIProcessPathAndPID ProcessHelper::getFirstProcessOfManyANSI(vector<string> paths) {
	ANSIProcessPathAndPID processPathAndPID = {"", 0};
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (Process32First(snapshot, &entry)) {
		do {
			for (auto &path : paths) {
	#if WINVER > _WIN32_WINNT_NT4
				if (_tcsicmp(entry.szExeFile, StringHelper::stringToWideString(path).c_str()) == 0) {
	#else
				if (_tcsicmp(entry.szExeFile, path.c_str()) == 0) {
	#endif
					processPathAndPID.pid = entry.th32ProcessID;
					processPathAndPID.path = path;
					CloseHandle(snapshot);
					return processPathAndPID;
				}
			}
		} while (Process32Next(snapshot, &entry));
	}
	CloseHandle(snapshot);
	return processPathAndPID;
}
#else
ProcessPathAndPID ProcessHelper::getFirstProcessOfMany(vector<string> paths) {
	ProcessPathAndPID processPathAndPID = {"", 0};
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (Process32First(snapshot, &entry)) {
		do {
			for (auto &path : paths) {
				if (_tcsicmp(entry.szExeFile, path.c_str()) == 0) {
					processPathAndPID.pid = entry.th32ProcessID;
					processPathAndPID.path = path;
					CloseHandle(snapshot);
					return processPathAndPID;
				}
			}
		} while (Process32Next(snapshot, &entry));
	}
	CloseHandle(snapshot);
	return processPathAndPID;
}
#endif

#if WINVER > _WIN32_WINNT_NT4
ProcessPathAndPID ProcessHelper::getFirstProcessOfMany(vector<wstring> paths) {
	ProcessPathAndPID processPathAndPID = {L"", 0};
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (Process32First(snapshot, &entry)) {
		do {
			for (auto &path : paths) {
				if (_tcsicmp(entry.szExeFile, path.c_str()) == 0) {
					processPathAndPID.pid = entry.th32ProcessID;
					processPathAndPID.path = path;
					CloseHandle(snapshot);
					return processPathAndPID;
				}
			}
		} while (Process32Next(snapshot, &entry));
	}
	CloseHandle(snapshot);
	return processPathAndPID;
}
#endif

BOOL CALLBACK ProcessHelper::enumWindowsProc(HWND hwnd, LPARAM lParam) {
	DWORD processId;
	GetWindowThreadProcessId(hwnd, &processId);

	if (processId == *((DWORD *)lParam)) {
		*((HWND *)lParam) = hwnd;
		return FALSE;
	}

	return TRUE;
}

#if WINVER > _WIN32_WINNT_NT4
BOOL CALLBACK ProcessHelper::enumDisplayWindows(HWND hwnd, LPARAM lParam) {
	HWND *window = reinterpret_cast<HWND *>(lParam);
	wchar_t windowTitle[256];
	GetWindowText(hwnd, windowTitle, sizeof(windowTitle));
	wstring title(windowTitle);

	int displayPropertiesId = 41; // ID for localized "Display" string according to resource hacker

	wstring displayString = StringHelper::getWideStringFromLibrary(L"desk.cpl", displayPropertiesId);

	if (boost::icontains(title, displayString)) {
		*window = hwnd;
		return FALSE;
	}

	return TRUE;
}

HWND ProcessHelper::findMainWindow(wstring path) {
	HWND hwnd = NULL;
	DWORD processId = getProcessId(path);
	EnumWindows(enumWindowsProc, (LPARAM)&processId);
	return (HWND)processId;
}

HWND ProcessHelper::findDisplaySettingsWindow() {
	HWND hwnd = NULL;
	EnumWindows(enumDisplayWindows, (LPARAM)&hwnd);
	return hwnd;
}

void ProcessHelper::setToForeground(wstring file) {
	DWORD processId = getProcessId(file);
	HWND window = findMainWindow(processId);
	setToForeground(window);
}

void ProcessHelper::killProcess(wstring path, int exitCode) {
	DWORD pid = getProcessId(path);
	if (pid == 0)
		return;
	HANDLE handle = OpenProcess(PROCESS_TERMINATE, false, pid);
	if (handle == NULL)
		throw InteractBoxException(ErrorCodes::CannotOpenProcess, path);
	bool success = TerminateProcess(handle, exitCode);
	if (!success)
		throw InteractBoxException(ErrorCodes::CannotTerminateProcess, path);
	success = CloseHandle(handle);
	if (!success)
		throw InteractBoxException(ErrorCodes::CannotCloseHandle, path);
}
#endif

HWND ProcessHelper::findMainWindow(DWORD processId) {
	HWND hwnd = NULL;
	EnumWindows(enumWindowsProc, (LPARAM)&processId);
	return (HWND)processId;
}

HWND ProcessHelper::findMainWindow(string path) {
	HWND hwnd = NULL;
	DWORD processId = getProcessId(path);
	EnumWindows(enumWindowsProc, (LPARAM)&processId);
	return (HWND)processId;
}

void ProcessHelper::setToForeground(HWND hwnd) {
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

void ProcessHelper::setToForeground(string file) {
	DWORD processId = getProcessId(file);
	HWND window = findMainWindow(processId);
	setToForeground(window);
}

void ProcessHelper::killProcess(string path, int exitCode) {
	DWORD pid = getProcessId(path);
	if (pid == 0)
		return;
	HANDLE handle = OpenProcess(PROCESS_TERMINATE, false, pid);
	if (handle == NULL)
		throw InteractBoxException(ErrorCodes::CannotOpenProcess, path);
	bool success = TerminateProcess(handle, exitCode);
	if (!success)
		throw InteractBoxException(ErrorCodes::CannotTerminateProcess, path);
	success = CloseHandle(handle);
	if (!success)
		throw InteractBoxException(ErrorCodes::CannotCloseHandle, path);
}

void ProcessHelper::killProcess(DWORD pid, int exitCode) {
	if (pid == 0)
		return;
	HANDLE handle = OpenProcess(PROCESS_TERMINATE, false, pid);
	if (handle == NULL)
		throw InteractBoxException(ErrorCodes::CannotOpenProcess);
	bool success = TerminateProcess(handle, exitCode);
	if (!success)
		throw InteractBoxException(ErrorCodes::CannotTerminateProcess);
	success = CloseHandle(handle);
	if (!success)
		throw InteractBoxException(ErrorCodes::CannotCloseHandle);
}