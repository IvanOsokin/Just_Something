#include "Asserts/Asserts.h"
#include "Log/Log.h"

namespace Core
{
	void DebugBreak()
	{
#ifdef _DEBUG
		__debugbreak();
#endif
	}

	void HandleAssertion(const std::string& message, int line, const char* file)
	{
		GetLogger().Message(LogMessageSeverity::Error, message, line, file);
		DebugBreak();
	}
}
