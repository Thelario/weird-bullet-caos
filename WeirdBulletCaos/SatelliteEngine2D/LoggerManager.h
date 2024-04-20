#pragma once

#include <string>

namespace Satellite
{
	class LoggerManager
	{
		public:
			void Log(const std::string& message);
			void Warning(const std::string& message);
			void Error(const std::string& message);
			void Error(const std::string& message, const char* error);
	};
}