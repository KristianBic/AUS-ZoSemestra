#include "file_log_consumer.h"
using namespace structures;

structures::FileLogConsumer::FileLogConsumer(const std::string& path) : fileStream_(path)
{
	if (!fileStream_.is_open()) {
		throw std::runtime_error("Failed to open file " + path);
	}
}

void FileLogConsumer::logMessage(LogType type, const std::string& message) {
	fileStream_ << logTypeToString(type) << ';' << message << std::endl;
}

void FileLogConsumer::logDuration(DurationType duration, const std::string& message)
{
	fileStream_ << logTypeToString(LogType::Duration) << ';' << duration.count() << ';' << message << ';' << std::endl;
}