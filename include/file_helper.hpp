#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include <shlobj.h>
#include <shlwapi.h>
#include <winver.h>
#if WINVER > _WIN32_WINNT_NT4
#include <knownfolders.h>
#endif
#include <boost/algorithm/string.hpp>
#include "shared.hpp"
#include "string_helper.hpp"
#include "errors/error_codes.hpp"
#include "errors/interact_box_exceptions.hpp"


class FileHelper {
	public:

		#if WINVER > _WIN32_WINNT_NT4
		static bool fileHasValidExtension(const std::wstring& fileName, std::vector<std::wstring> extensions);

		static void removeFolder(std::wstring folder);

		static HANDLE makeFile(std::wstring filePath, bool createNew = true);

		static void createDirectory(std::wstring dirPath);

		static std::string readFileAsString(std::wstring filePath);
		static std::wstring readFileAsWideString(std::wstring filePath);
		static std::wstring readFileAsWideString(std::string filePath);

		static HANDLE loadImageFile(std::wstring filePath);

		static void writeToFile(std::wstring filePath, std::wstring content);
		static void writeToFile(HANDLE hFile, std::wstring content);

		static std::wstring getWindowsDirectory();

		static bool checkIfFileExists(std::wstring filePath);

		static bool renameFile(std::wstring oldPath, std::wstring newPath);

		static bool isInsideDirectory(std::wstring& file, std::wstring& directory);

		static std::vector<std::wstring> filterFiles(std::vector<std::wstring> files, std::vector<std::wstring> extensions);
		static std::vector<std::wstring> filterFiles(std::vector<std::wstring> files, std::wstring directory);

		static bool deleteFile(std::wstring fileName);

		static std::vector<std::wstring> listFiles(const std::wstring& directory);
		static std::vector<std::wstring> listFilesWithoutFailures(const std::wstring& directory);

		static std::wstring getExecutableFileName();
		static std::string getExecutableFileNameAsString();

		static std::wstring getWorkingDirectory();
		static std::string getWorkingDirectoryAsString();

		#if WINVER >= _WIN32_WINNT_VISTA
		static std::wstring getAppDataPath();
		#endif

		static bool copyFile(std::wstring oldPath, std::wstring newPath);

		#else
		static bool fileHasValidExtension(const std::string& fileName, std::vector<std::string> extensions);

		static void removeFolder(std::string folder);

		static std::string getWindowsDirectory();

		static bool checkIfFileExists(std::string filePath);

		static bool renameFile(std::string oldPath, std::string newPath);

		static bool isInsideDirectory(std::string& file, std::string& directory);

		static std::vector<std::string> filterFiles(std::vector<std::string> files, std::vector<std::string> extensions);
		static std::vector<std::string> filterFiles(std::vector<std::string> files, std::string directory);

		static std::vector<std::string> listFiles(const std::string& directory);
		static std::vector<std::string> listFilesWithoutFailures(const std::string& directory);

		static std::string getExecutableFileName();
		static std::string getWorkingDirectory();

		static std::string getVolumeSerial();
		
		#endif

		static HANDLE makeFile(std::string filePath, bool createNew = true);

		static std::string getFileVersion(std::string filePath);		

		static void createDirectory(std::string dirPath);
		
		static std::string readFileAsString(std::string filePath);

		static HANDLE loadImageFile(std::string filePath);

		
		static void writeToFile(std::string filePath, std::string content);
		static void writeToFile(HANDLE hFile, std::string content);

		static long getFileSize(HANDLE hFile);
		static void closeFile(HANDLE hFile);

		
		static bool deleteFile(std::string fileName);

		static bool copyFile(std::string oldPath, std::string newPath);
};