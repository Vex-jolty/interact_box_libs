#include "file_helper.hpp"

using namespace std;
#if WINVER > _WIN32_WINNT_NT4
bool FileHelper::fileHasValidExtension(const wstring& fileName, vector<wstring> extensions) {
	for (const auto& ext : extensions) {
		if (fileName.size() < ext.size() ||
			fileName.compare(fileName.size() - ext.size(), ext.size(), ext) != 0) {
			continue;
		}
		return true;
	}
	return false;
}

vector<wstring> FileHelper::listFiles(const wstring& directory) {
	vector<wstring> files;
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFileW((directory + L"\\*").c_str(), &findFileData);

	if (hFind == INVALID_HANDLE_VALUE) {
		throw InteractBoxException(ErrorCodes::CannotAccessDirectory, directory);
	}

	do {
		const wstring fileOrDirectory = findFileData.cFileName;
		if (fileOrDirectory == L"." || fileOrDirectory == L"..") {
			continue;
		}
		wstring fullPath = directory + L"\\" + fileOrDirectory;

		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			listFiles(fullPath);
		} else {
			files.push_back(fullPath);
		}
	} while (FindNextFile(hFind, &findFileData) != 0);

	FindClose(hFind);
	return files;
}

vector<wstring> FileHelper::listFilesWithoutFailures(const wstring& directory) {
	vector<wstring> files;
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFileW((directory + L"\\*").c_str(), &findFileData);

	if (hFind == INVALID_HANDLE_VALUE) {
		return files;
	}

	do {
		const wstring fileOrDirectory = findFileData.cFileName;
		if (fileOrDirectory == L"." || fileOrDirectory == L"..") {
			continue;
		}
		wstring fullPath = directory + L"\\" + fileOrDirectory;

		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			listFilesWithoutFailures(fullPath);
		} else {
			files.push_back(fullPath);
		}
	} while (FindNextFile(hFind, &findFileData) != 0);

	FindClose(hFind);
	return files;
}

void FileHelper::removeFolder(wstring folder) {
	bool success = RemoveDirectory(folder.c_str());
	if (!success) throw InteractBoxException(ErrorCodes::CannotDeleteDirectory, folder);
}

wstring FileHelper::getExecutableFileName() {
	wchar_t buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	return wstring(buffer);
}

string FileHelper::getExecutableFileNameAsString() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	return string(buffer);
}

wstring FileHelper::getWorkingDirectory() {
	wstring exePath = getExecutableFileName();
	size_t pos = exePath.find_last_of(L"\\/");
	wstring workingDirectory = exePath.substr(0, pos);
	return workingDirectory;
}

string FileHelper::getWorkingDirectoryAsString() {
	string exePath = getExecutableFileNameAsString();
	size_t pos = exePath.find_last_of("\\/");
	string workingDirectory = exePath.substr(0, pos);
	return workingDirectory;
}

HANDLE FileHelper::makeFile(wstring filePath, bool createNew) {
	return CreateFile(
		filePath.c_str(),
		GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,
		createNew ? CREATE_NEW : OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
}

wstring FileHelper::getWindowsDirectory() {
	wchar_t windowsDir[MAX_PATH];
	GetWindowsDirectory(windowsDir, MAX_PATH);
	return windowsDir;
}

void FileHelper::createDirectory(wstring dirPath) {
	bool success = CreateDirectoryW(dirPath.c_str(), NULL);
	if (!success) throw InteractBoxException(ErrorCodes::CannotCreateDirectory, dirPath);
}

string FileHelper::readFileAsString(wstring filePath) {
	HANDLE hFile = CreateFile(
		filePath.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE) {
		throw InteractBoxException(ErrorCodes::InvalidFileHandle, filePath);
	}
	DWORD fileSize = GetFileSize(hFile, NULL);
	DWORD bytesRead;
	if (fileSize == INVALID_FILE_SIZE) {
		throw InteractBoxException(ErrorCodes::InvalidFileSize, filePath);
	}
	wchar_t* buffer = new wchar_t[fileSize];
	ReadFile(hFile, buffer, fileSize, &bytesRead, NULL);
	closeFile(hFile);
	return StringHelper::wideStringToString(buffer);
}

wstring FileHelper::readFileAsWideString(wstring filePath) {
	HANDLE hFile = CreateFile(
		filePath.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE) {
		throw InteractBoxException(ErrorCodes::InvalidFileHandle, filePath);
	}
	DWORD fileSize = GetFileSize(hFile, NULL);
	DWORD bytesRead;
	if (fileSize == INVALID_FILE_SIZE) {
		throw InteractBoxException(ErrorCodes::InvalidFileSize, filePath);
	}
	wchar_t* buffer = new wchar_t[fileSize];
	ReadFile(hFile, buffer, fileSize, &bytesRead, NULL);
	closeFile(hFile);
	return buffer;
}

void FileHelper::writeToFile(wstring filePath, wstring content) {
	HANDLE hFile = makeFile(filePath, false);
	DWORD bytesWritten;
	bool writeOk = WriteFile(hFile, content.c_str(), content.size(), &bytesWritten, NULL);
	if (!writeOk) {
		throw InteractBoxException(ErrorCodes::CannotWriteToFile, filePath);
	}
	closeFile(hFile);
}

HANDLE FileHelper::loadImageFile(wstring filePath) {
	return LoadImage(
		NULL,
		filePath.c_str(),
		IMAGE_BITMAP,
		0,
		0,
		LR_LOADFROMFILE
	);
}

wstring FileHelper::readFileAsWideString(string filePath) {
	HANDLE hFile = CreateFileA(
		filePath.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE) {
		throw InteractBoxException(ErrorCodes::InvalidFileHandle, filePath);
	}
	DWORD fileSize = GetFileSize(hFile, NULL);
	DWORD bytesRead;
	if (fileSize == INVALID_FILE_SIZE) {
		throw InteractBoxException(ErrorCodes::InvalidFileSize, filePath);
	}
	char* buffer = new char[fileSize];
	ReadFile(hFile, buffer, fileSize, &bytesRead, NULL);
	closeFile(hFile);
	return StringHelper::stringToWideString(buffer);
}

wstring FileHelper::getAppDataPath() {
	wchar_t* path;
	SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &path);
	return wstring(path);
}

bool FileHelper::checkIfFileExists(wstring filePath) {
	DWORD dwAttrib = GetFileAttributes(filePath.c_str());
	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

bool FileHelper::renameFile(wstring oldPath, wstring newPath) {
	return MoveFile(oldPath.c_str(), newPath.c_str());
}

void FileHelper::writeToFile(HANDLE hFile, wstring content) {
	DWORD bytesWritten;
	bool writeOk = WriteFile(hFile, content.c_str(), content.size(), &bytesWritten, NULL);
	if (!writeOk) {
		throw InteractBoxException(ErrorCodes::CannotWriteToFile);
	}
}

vector<wstring> FileHelper::filterFiles(vector<wstring> files, vector<wstring> extensions) {
	vector<wstring> filteredFiles;
	wstring executableFilename = StringHelper::toLowercase(getExecutableFileName());
	auto extensionChecker = [&extensions, &executableFilename](const wstring& filename) {
		wstring lowerCaseName = StringHelper::toLowercase(filename);
		if (lowerCaseName == executableFilename) return false;
		return fileHasValidExtension(lowerCaseName, extensions);
		};
	copy_if(files.begin(), files.end(), back_inserter(filteredFiles), extensionChecker);
	return filteredFiles;
}

vector<wstring> FileHelper::filterFiles(vector<wstring> files, wstring directory) {
	vector<wstring> filteredFiles;
	wstring executableFilename = StringHelper::toLowercase(getExecutableFileName());
	wstring lowerCaseDirectory = StringHelper::toLowercase(directory);
	auto dirChecker = [&directory, &executableFilename, &lowerCaseDirectory](const wstring& filename) {
		wstring lowerCaseName = StringHelper::toLowercase(filename);
		if (lowerCaseName == executableFilename) return false;
		return lowerCaseName.starts_with(lowerCaseDirectory);
		};
	copy_if(files.begin(), files.end(), back_inserter(filteredFiles), dirChecker);
	return filteredFiles;
}

bool FileHelper::deleteFile(wstring fileName) {
	return DeleteFile(fileName.c_str());
}

bool FileHelper::copyFile(wstring oldPath, wstring newPath) {
	return CopyFileW(oldPath.c_str(), newPath.c_str(), false);
}

#else
bool FileHelper::fileHasValidExtension(const string& fileName, vector<string> extensions) {
	for (const auto& ext : extensions) {
		if (fileName.size() < ext.size() ||
			fileName.compare(fileName.size() - ext.size(), ext.size(), ext) != 0) {
			continue;
		}
		return true;
	}
	return false;
}

vector<string> FileHelper::listFiles(const string& directory) {
	vector<string> files;
	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = FindFirstFileA((directory + "\\*").c_str(), &findFileData);

	if (hFind == INVALID_HANDLE_VALUE) {
		throw InteractBoxException(ErrorCodes::CannotAccessDirectory, directory);
	}

	do {
		const string fileOrDirectory = findFileData.cFileName;
		if (fileOrDirectory == "." || fileOrDirectory == "..") {
			continue;
		}
		string fullPath = directory + "\\" + fileOrDirectory;

		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			listFiles(fullPath);
		} else {
			files.push_back(fullPath);
		}
	} while (FindNextFileA(hFind, &findFileData) != 0);

	FindClose(hFind);
	return files;
}

vector<string> FileHelper::listFilesWithoutFailures(const string& directory) {
	vector<string> files;
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFileA((directory + "\\*").c_str(), &findFileData);

	if (hFind == INVALID_HANDLE_VALUE) {
		return files;
	}

	do {
		const string fileOrDirectory = findFileData.cFileName;
		if (fileOrDirectory == "." || fileOrDirectory == "..") {
			continue;
		}
		string fullPath = directory + "\\" + fileOrDirectory;

		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			listFilesWithoutFailures(fullPath);
		} else {
			files.push_back(fullPath);
		}
	} while (FindNextFile(hFind, &findFileData) != 0);

	FindClose(hFind);
	return files;
}

bool FileHelper::isInsideDirectory(string& file, string& directory) {
  vector<string> splitFile = StringHelper::splitString(file, "\\");
	splitFile.pop_back();
	string fileDirectory = boost::algorithm::join(splitFile, "\\");
	return boost::algorithm::iequals(fileDirectory, directory);
}

bool FileHelper::checkIfFileExists(string filePath) {
	DWORD dwAttrib = GetFileAttributesA(filePath.c_str());
	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

bool FileHelper::renameFile(string oldPath, string newPath) {
	return MoveFileA(oldPath.c_str(), newPath.c_str());
}

void FileHelper::removeFolder(string folder) {
	bool success = RemoveDirectoryA(folder.c_str());
	if (!success) throw InteractBoxException(ErrorCodes::CannotDeleteDirectory, folder);
}

string FileHelper::getExecutableFileName() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	return string(buffer);
}

string FileHelper::getVolumeSerial() {
	char volumeName[MAX_PATH + 1] = { 0 };
	char fileSystemName[MAX_PATH + 1] = { 0 };
	DWORD serialNumber = 0;
	DWORD maxComponentLen = 0;
	DWORD fileSystemFlags = 0;
	BOOL result = GetVolumeInformationA(
		"C:\\",
		volumeName,
		ARRAYSIZE(volumeName),
		&serialNumber,
		&maxComponentLen,
		&fileSystemFlags,
		fileSystemName,
		ARRAYSIZE(fileSystemName)
	);
	if (!result) return string();
	char serialStr[20];
	sprintf(serialStr, "%08X", serialNumber);
	return string(serialStr);
}

string FileHelper::getWorkingDirectory() {
	string exePath = getExecutableFileName();
	size_t pos = exePath.find_last_of("\\/");
	string workingDirectory = exePath.substr(0, pos);
	return workingDirectory;
}

string FileHelper::getWindowsDirectory() {
	char windowsDir[MAX_PATH];
	GetWindowsDirectoryA(windowsDir, MAX_PATH);
	return windowsDir;
}

vector<string> FileHelper::filterFiles(vector<string> files, vector<string> extensions) {
	vector<string> filteredFiles;
	string executableFilename = StringHelper::toLowercase(getExecutableFileName());
	auto extensionChecker = [&extensions, &executableFilename](const std::string& filename) {
		string lowerCaseName = StringHelper::toLowercase(filename);
		if (lowerCaseName == executableFilename) return false;
		return fileHasValidExtension(lowerCaseName, extensions);
		};
	copy_if(files.begin(), files.end(), back_inserter(filteredFiles), extensionChecker);
	return filteredFiles;
}

vector<string> FileHelper::filterFiles(vector<string> files, string directory) {
	vector<string> filteredFiles;
	string executableFilename = StringHelper::toLowercase(getExecutableFileName());
	string lowerCaseDirectory = StringHelper::toLowercase(directory);
	auto dirChecker = [&directory, &executableFilename, &lowerCaseDirectory](const std::string& filename) {
		string lowerCaseName = StringHelper::toLowercase(filename);
		if (lowerCaseName == executableFilename) return false;
		return lowerCaseName.starts_with(lowerCaseDirectory);
		};
	copy_if(files.begin(), files.end(), back_inserter(filteredFiles), dirChecker);
	return filteredFiles;
}

#endif

HANDLE FileHelper::makeFile(string filePath, bool createNew) {
	return CreateFileA(
		filePath.c_str(),
		GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,
		createNew ? CREATE_NEW : OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
}

string FileHelper::getFileVersion(string filePath) {
	DWORD versionHandle = 0;
	UINT size = 0;
	LPBYTE lpBuffer = NULL;
	DWORD versionSize = GetFileVersionInfoSizeA(filePath.c_str(), &versionHandle);
	LPSTR versionData = new char[versionSize];
	GetFileVersionInfoA(filePath.c_str(), versionHandle, versionSize, versionData);
	VerQueryValueA(versionData, "\\", (VOID FAR * FAR*) & lpBuffer, &size);
	VS_FIXEDFILEINFO* verInfo = (VS_FIXEDFILEINFO*)lpBuffer;
	char* versionString;
	sprintf(
		versionString,
		"%d.%d.%d.%d",
		(verInfo->dwFileVersionMS >> 16) & 0xffff,
		(verInfo->dwFileVersionMS >> 0) & 0xffff,
		(verInfo->dwFileVersionLS >> 16) & 0xffff,
		(verInfo->dwFileVersionLS >> 0) & 0xffff
	);
	delete[] versionData;
	return versionString;
}

void FileHelper::createDirectory(string dirPath) {
	bool success = CreateDirectoryA(dirPath.c_str(), NULL);
	if (!success) throw InteractBoxException(ErrorCodes::CannotCreateDirectory, dirPath);
}

string FileHelper::readFileAsString(string filePath) {
	HANDLE hFile = CreateFileA(
		filePath.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE) {
		throw InteractBoxException(ErrorCodes::InvalidFileHandle, filePath);
	}
	DWORD fileSize = GetFileSize(hFile, NULL);
	DWORD bytesRead;
	if (fileSize == INVALID_FILE_SIZE) {
		throw InteractBoxException(ErrorCodes::InvalidFileSize, filePath);
	}
	char* buffer = new char[fileSize];
	ReadFile(hFile, buffer, fileSize, &bytesRead, NULL);
	closeFile(hFile);
	return buffer;
}

HANDLE FileHelper::loadImageFile(string filePath) {
	return LoadImageA(
		NULL,
		filePath.c_str(),
		IMAGE_BITMAP,
		0,
		0,
		LR_LOADFROMFILE
	);
}

void FileHelper::closeFile(HANDLE hFile) {
	bool closeOk = CloseHandle(hFile);
	if (!closeOk) {
		throw InteractBoxException(ErrorCodes::CannotCloseHandle);
	}
}

void FileHelper::writeToFile(string filePath, string content) {
	HANDLE hFile = makeFile(filePath, false);
	DWORD bytesWritten;
	bool writeOk = WriteFile(hFile, content.c_str(), content.size(), &bytesWritten, NULL);
	if (!writeOk) {
		throw InteractBoxException(ErrorCodes::CannotWriteToFile, filePath);
	}
	closeFile(hFile);
}

void FileHelper::writeToFile(HANDLE hFile, string content) {
	DWORD bytesWritten;
	bool writeOk = WriteFile(hFile, content.c_str(), content.size(), &bytesWritten, NULL);
	if (!writeOk) {
		throw InteractBoxException(ErrorCodes::CannotWriteToFile);
	}
}

long FileHelper::getFileSize(HANDLE hFile) {
	DWORD size = GetFileSize(hFile, NULL);
	return size;
}

bool FileHelper::deleteFile(string fileName) {
	return DeleteFileA(fileName.c_str());
}

bool FileHelper::copyFile(string oldPath, string newPath) {
	return CopyFileA(oldPath.c_str(), newPath.c_str(), false);
}

BOOL WINAPI DllMain(
	HINSTANCE dllInstanceHandle,
	DWORD reason,
	LPVOID reserved
) {
	switch (reason) {
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_PROCESS_DETACH:
			break;

		default:
			return FALSE;
	}
	return TRUE;
}