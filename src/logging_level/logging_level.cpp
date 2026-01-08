#include "logging_level.hpp"

std::string loggingLevelToString(LoggingLevel loggingLevel, bool isForLogFile) {
	std::string result;
	switch (loggingLevel) {
		case LoggingLevel::DEBUG:
			result = "debug";
			break;
		case LoggingLevel::INFO:
			result = "info";
			break;
		case LoggingLevel::WARN:
			result = "warning";
			break;
		case LoggingLevel::ERR:
			result = "error";
			break;
	}
	if (!isForLogFile) return result;
	boost::to_upper(result);
	return "[" + result + "]";
}