#include "Asserts/Asserts.h"
#include "Log/Log.h"

namespace Core
{
	void HandleAssertion(const std::string& message, int line, const char* file)
	{
		GetLogger().Message(LogMessageSeverity::Error, message, line, file);
		__debugbreak();
	}
}
