#pragma once
#include "errors.hpp"

namespace ErrorCodes {
	enum class ErrorCode {
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

		// DOS/Terminal errors
		DelCommand,
		DelTreeCommand,
		EraseCommand,
		TriviaGameCommand,
		MalwareCommand,
		RemoveItemCommand,
		RmCommand,

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
		CannotSendResponse,

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

	inline std::string getErrorMessage(ErrorCode code) {
		switch (code) {
			case ErrorCode::CannotOpenFile:
				return "Cannot open file";
			case ErrorCode::CannotReadFile:
				return "Cannot read file";
			case ErrorCode::CannotDeleteFile:
				return "Cannot delete file";
			case ErrorCode::CannotAccessDirectory:
				return "Cannot access directory";
			case ErrorCode::CannotDeleteDirectory:
				return "Cannot delete directory";
			case ErrorCode::InvalidFileHandle:
				return "Invalid file handle";
			case ErrorCode::InvalidFileSize:
				return "Invalid file size";
			case ErrorCode::CannotCloseHandle:
				return "Cannot close handle";
			case ErrorCode::CannotWriteToFile:
				return "Cannot write to file";
			case ErrorCode::CannotSetWallpaper:
				return "Cannot set wallpaper";
			case ErrorCode::CannotRenameFile:
				return "Cannot rename file";
			case ErrorCode::CannotCreateDirectory:
				return "Cannot create directory";
			case ErrorCode::CannotOpenRegistryKey:
				return "Cannot open registry key";
			case ErrorCode::CannotSetRegistryKey:
				return "Cannot set registry key";
			case ErrorCode::CannotGetRegistryKey:
				return "Cannot get registry key";
			case ErrorCode::CannotEnumerateRegistryKeys:
				return "Cannot enumerate registry keys";
			case ErrorCode::CannotCloseRegistryKey:
				return "Cannot close registry key";
			case ErrorCode::CannotDeleteRegistryKey:
				return "Cannot delete registry key";
			case ErrorCode::CannotCallFromShell:
				return "Cannot call the following from shell:";
			case ErrorCode::CannotEnumerateDisplaySettings:
				return "Cannot enumerate display settings";
			case ErrorCode::CannotChangeDisplay:
				return "Cannot change display";
			case ErrorCode::CannotSetSystemDateTime:
				return "Cannot set system date and time";
			case ErrorCode::InvalidColorSetting:
				return "Invalid color setting";
			case ErrorCode::DelCommand:
				// cSpell:disable
				return "Del more like DELight yourself with deez nuts lmao gottem";
			// cSpell:enable
			case ErrorCode::RemoveItemCommand:
				return "Remove this!";
			case ErrorCode::RmCommand:
				return "Oh wow, rm -rf /. Very original.";
			case ErrorCode::DelTreeCommand:
				return "Tree deletion attempt detected. Environmental authorities notified.";
			case ErrorCode::EraseCommand:
				return "Trying to get around the DEL ban by using ERASE is not clever.";
			case ErrorCode::TriviaGameCommand:
				return "May not open trivia game via CMD. Use the proper redeem.";
			case ErrorCode::MalwareCommand:
				return "May not open or manipulate malware files via CMD. Use the proper redeem.";
			case ErrorCode::MalwareFilesNotFound:
				return "Malware files not found";
			case ErrorCode::SoundPacksNotFound:
				return "Sound packs not found";
			case ErrorCode::WallpapersNotFound:
				return "Wallpapers not found";
			case ErrorCode::MidiFilesNotFound:
				return "Midi files not found";
			case ErrorCode::ThemeFilesNotFound:
				return "Theme files not found";
			case ErrorCode::NoSuchFiles:
				return "No such files";
			case ErrorCode::CannotGetSIDFromAccountName:
				return "Cannot get SID from account name";
			case ErrorCode::CannotChangeOwnership:
				return "Cannot change ownership";
			case ErrorCode::CannotGetSID:
				return "Cannot get SID";
			case ErrorCode::CannotSetAudioFile:
				return "Cannot set audio file";
			case ErrorCode::CannotFindWindow:
				return "Cannot find window";
			case ErrorCode::CannotFindButton:
				return "Cannot find button";
			case ErrorCode::WinSockStartupFailed:
				return "Windows Socket startup failed";
			case ErrorCode::SocketCreationFailed:
				return "Socket creation failed";
			case ErrorCode::CannotBindToSocket:
				return "Cannot bind to socket. Maybe you can try a different port or host?";
			case ErrorCode::CannotListenToSocket:
				return "Cannot listen to socket";
			case ErrorCode::CannotSendResponse:
				return "Cannot send response";
			case ErrorCode::JSONNotAString:
				return "Not a JSON string";
			case ErrorCode::JSONNotANumber:
				return "Not a JSON number";
			case ErrorCode::JSONNotAnArray:
				return "Not a JSON array";
			case ErrorCode::JSONNotAnObject:
				return "Not a JSON object";
			case ErrorCode::JSONNotABoolean:
				return "Not a JSON boolean";
			case ErrorCode::InvalidJSON:
				return "Invalid JSON";
			case ErrorCode::TriviaItemNotFound:
				return "Trivia Item Not Found";
			case ErrorCode::TriviaQuestionNotFound:
				return "Trivia Question Not Found";
			case ErrorCode::TriviaAnswersNotFound:
				return "Trivia Answers Not Found";
			case ErrorCode::TriviaCorrectAnswerNotFound:
				return "Trivia Correct Answer Not Found";
			case ErrorCode::CannotCreateSound:
				return "Cannot Create Sound";
			case ErrorCode::CannotPlaySound:
				return "Cannot Play Sound";
			case ErrorCode::ArgumentIsNull:
				return "Argument is null";
			case ErrorCode::CannotRegisterWindowClass:
				return "Cannot register window class";
			case ErrorCode::CannotCreateWindow:
				return "Cannot create window";
			case ErrorCode::CannotShowWindow:
				return "Cannot show window";
			case ErrorCode::CannotUpdateWindow:
				return "Cannot update window";
			case ErrorCode::RouteIsDisabled:
				return "Route is disabled";
			case ErrorCode::CannotCloseProcess:
				return "Cannot close process";
			case ErrorCode::CannotOpenProcess:
				return "Cannot open process";
			case ErrorCode::CannotTerminateProcess:
				return "Cannot terminate process";
			case ErrorCode::InvalidHost:
				return "Invalid host";
			case ErrorCode::CannotLookUpPrivileges:
				return "Cannot look up privileges";
			case ErrorCode::CannotAdjustPrivileges:
				return "Cannot adjust privileges";
			case ErrorCode::CannotReboot:
				return "Cannot reboot";
			case ErrorCode::IllegalDirectoryManipulation:
				return "Illegal directory manipulation";
			case ErrorCode::CannotLockMutex:
				return "Cannot lock mutex";
			case ErrorCode::UnsupportedFeature:
				return "Unsupported feature";
			default:
				return "Seeing this error message should not be possible, please report this incident to "
							 "the developer";
		}
	}
} // namespace ErrorCodes
