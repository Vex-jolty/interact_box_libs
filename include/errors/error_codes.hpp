#pragma once
#include "errors.hpp"


namespace ErrorCodes {
	enum ErrorCode {
		// File errors
		CannotOpenFile,
		CannotReadFile,
		CannotDeleteFile,
		CannotAccessDirectory,
		CannotDeleteDirectory,
		InvalidFileHandle,
		InvalidFileSize,
		CannotCloseHandle,
		CannotWriteToFile,
		CannotSetWallpaper,
		CannotRenameFile,
		CannotCreateDirectory,

		// Registry errors
		CannotOpenRegistryKey,
		CannotSetRegistryKey,
		CannotGetRegistryKey,
		CannotEnumerateRegistryKeys,
		CannotCloseRegistryKey,
		CannotDeleteRegistryKey,

		// Shell error
		CannotCallFromShell,

		// Resolution errors
		CannotEnumerateDisplaySettings,
		CannotChangeDisplay,
		InvalidColorSetting,

		// Time error
		CannotSetSystemDateTime,

		// DOS errors
		DelCommand,
		DelTreeCommand,
		EraseCommand,
		TriviaGameCommand,
		MalwareCommand,
		RemoveItemCommand,

		// File collection errors
		MalwareFilesNotFound,
		SoundPacksNotFound,
		WallpapersNotFound,
		MidiFilesNotFound,
		ThemeFilesNotFound,
		NoSuchFiles,

		// Ownership errors
		CannotGetSIDFromAccountName,
		CannotChangeOwnership,
		CannotGetSID,

		// Audio error
		CannotSetAudioFile,

		// Window errors
		CannotFindWindow,
		CannotFindButton,

		// Server errors
		WinSockStartupFailed,
		SocketCreationFailed,
		CannotBindToSocket,
		CannotListenToSocket,

		// Json errors
		JSONNotAString,
		JSONNotANumber,
		JSONNotAnArray,
		JSONNotAnObject,
		JSONNotABoolean,
		InvalidJSON,

		// Trivia errors
		TriviaItemNotFound,
		TriviaQuestionNotFound,
		TriviaAnswersNotFound,
		TriviaCorrectAnswerNotFound,

		// Audio errors
		CannotCreateSound,
		CannotPlaySound,

		// Null error
		ArgumentIsNull,

		// Window errors
		CannotRegisterWindowClass,
		CannotCreateWindow,
		CannotShowWindow,
		CannotUpdateWindow,

		// Resource errors
		CannotFindResource,

		// Route errors
		RouteIsDisabled,

		// Process errors
		CannotOpenProcess,
		CannotTerminateProcess,
		CannotCloseProcess,
		CannotLookUpPrivileges,
		CannotAdjustPrivileges,

		// Config errors
		InvalidHost,

		// Reboot error
		CannotReboot,

		// Others
		IllegalDirectoryManipulation,
		CannotLockMutex,
		UnsupportedFeature,
	};

	DllExport inline std::string getErrorMessage(ErrorCode code) {
		switch (code) {
			case CannotOpenFile:
				return "Cannot open file";
			case CannotReadFile:
				return "Cannot read file";
			case CannotDeleteFile:
				return "Cannot delete file";
			case CannotAccessDirectory:
				return "Cannot access directory";
			case CannotDeleteDirectory:
				return "Cannot delete directory";
			case InvalidFileHandle:
				return "Invalid file handle";
			case InvalidFileSize:
				return "Invalid file size";
			case CannotCloseHandle:
				return "Cannot close handle";
			case CannotWriteToFile:
				return "Cannot write to file";
			case CannotSetWallpaper:
				return "Cannot set wallpaper";
			case CannotRenameFile:
				return "Cannot rename file";
			case CannotCreateDirectory:
				return "Cannot create directory";
			case CannotOpenRegistryKey:
				return "Cannot open registry key";
			case CannotSetRegistryKey:
				return "Cannot set registry key";
			case CannotGetRegistryKey:
				return "Cannot get registry key";
			case CannotEnumerateRegistryKeys:
				return "Cannot enumerate registry keys";
			case CannotCloseRegistryKey:
				return "Cannot close registry key";
			case CannotDeleteRegistryKey:
				return "Cannot delete registry key";
			case CannotCallFromShell:
				return "Cannot call the following from shell:";
			case CannotEnumerateDisplaySettings:
				return "Cannot enumerate display settings";
			case CannotChangeDisplay:
				return "Cannot change display";
			case CannotSetSystemDateTime:
				return "Cannot set system date and time";
			case InvalidColorSetting:
				return "Invalid color setting";
			case DelCommand:
			// cSpell:disable
				return "Del more like DELight yourself with deez nuts lmao gottem";
			// cSpell:enable
			case RemoveItemCommand:
				return "Remove this!";
			case DelTreeCommand:
				return "Tree deletion attempt detected. Environmental authorities notified.";
			case EraseCommand:
				return "Trying to get around the DEL ban by using ERASE is not clever.";
			case TriviaGameCommand:
				return "May not open trivia game via CMD. Use the proper redeem.";
			case MalwareCommand:
				return "May not open or manipulate malware files via CMD. Use the proper redeem.";
			case MalwareFilesNotFound:
				return "Malware files not found";
			case SoundPacksNotFound:
				return "Sound packs not found";
			case WallpapersNotFound:
				return "Wallpapers not found";
			case MidiFilesNotFound:
				return "Midi files not found";
			case ThemeFilesNotFound:
				return "Theme files not found";
			case NoSuchFiles:
				return "No such files";
			case CannotGetSIDFromAccountName:
				return "Cannot get SID from account name";
			case CannotChangeOwnership:
				return "Cannot change ownership";
			case CannotGetSID:
				return "Cannot get SID";
			case CannotSetAudioFile:
				return "Cannot set audio file";
			case CannotFindWindow:
				return "Cannot find window";
			case CannotFindButton:
				return "Cannot find button";
			case WinSockStartupFailed:
				return "Windows Socket startup failed";
			case SocketCreationFailed:
				return "Socket creation failed";
			case CannotBindToSocket:
				return "Cannot bind to socket";
			case CannotListenToSocket:
				return "Cannot listen to socket";
			case JSONNotAString:
				return "Not a JSON string";
			case JSONNotANumber:
				return "Not a JSON number";
			case JSONNotAnArray:
				return "Not a JSON array";
			case JSONNotAnObject:
				return "Not a JSON object";
			case JSONNotABoolean:
				return "Not a JSON boolean";
			case InvalidJSON:
				return "Invalid JSON";
			case TriviaItemNotFound:
				return "Trivia Item Not Found";
			case TriviaQuestionNotFound:
				return "Trivia Question Not Found";
			case TriviaAnswersNotFound:
				return "Trivia Answers Not Found";
			case TriviaCorrectAnswerNotFound:
				return "Trivia Correct Answer Not Found";
			case CannotCreateSound:
				return "Cannot Create Sound";
			case CannotPlaySound:
				return "Cannot Play Sound";
			case ArgumentIsNull:
				return "Argument is null";
			case CannotRegisterWindowClass:
				return "Cannot register window class";
			case CannotCreateWindow:
				return "Cannot create window";
			case CannotShowWindow:
				return "Cannot show window";
			case CannotUpdateWindow:
				return "Cannot update window";
			case RouteIsDisabled:
				return "Route is disabled";
			case CannotCloseProcess:
				return "Cannot close process";
			case CannotOpenProcess:
				return "Cannot open process";
			case CannotTerminateProcess:
				return "Cannot terminate process";
			case InvalidHost:
				return "Invalid host";
			case CannotLookUpPrivileges:
				return "Cannot look up privileges";
			case CannotAdjustPrivileges:
				return "Cannot adjust privileges";
			case CannotReboot:
				return "Cannot reboot";
			case IllegalDirectoryManipulation:
				return "Illegal directory manipulation";
			case CannotLockMutex:
				return "Cannot lock mutex";
			case UnsupportedFeature:
				return "Unsupported feature";
			default:
				return "Seeing this error message should not be possible, please report this incident to the developer";
		}
	}
}

