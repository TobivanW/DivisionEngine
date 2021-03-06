#include "LoggerPool.h"

namespace Division
{
	std::unordered_map<std::string, Logger*> LoggerPool::logPool_;

	LoggerPool::LoggerPool()
	{
	}



	LoggerPool* LoggerPool::getInstance()
	{
		static LoggerPool* instance_;
		return instance_;
	}



	Logger* Division::LoggerPool::getLogger(std::string name)
	{

		std::unordered_map<std::string, Logger*>::const_iterator found = logPool_.find(name);
		
		Logger* retrievedLogger = NULL;

		if (found == logPool_.end()) {
			retrievedLogger = new Logger(name);
			logPool_.insert(std::make_pair(name, retrievedLogger));
		}
		else {
			retrievedLogger = found->second;
		}
		
		return retrievedLogger;
	}



	LoggerPool::~LoggerPool()
	{
		std::unordered_map<std::string, Logger*>::const_iterator toBeDeleted = logPool_.begin();
		while (toBeDeleted != logPool_.end()) {
			delete toBeDeleted->second;
		}
		logPool_.clear();
	}

}