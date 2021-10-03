#pragma once

namespace Core
{
	class LogSink
	{
	public:
		virtual ~LogSink() = default;

		virtual void OnMessage(const LogMessageData & messageData) = 0;
	};
}
