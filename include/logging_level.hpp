#pragma once
#include <string>
#include <boost/algorithm/string.hpp>

enum LoggingLevel {
	DEBUG,
	INFO,
	WARN,
	ERR,
};

std::string loggingLevelToString(LoggingLevel loggingLevel, bool isForLogFile = false);