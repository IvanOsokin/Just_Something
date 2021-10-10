#pragma once

namespace Core
{
	void DebugBreak();
	void HandleAssertion(const std::string & message, int line, const char * file);
}