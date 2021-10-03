#pragma once

namespace Core
{
	struct LogMessageData;
	enum class LogMessageSeverity;
	class LogSink;

	class Log
	{
	public:
		using SinkPtr = std::shared_ptr<LogSink>;
		using Sinks = std::vector<SinkPtr>;
		
		static Log & Instance();

		void Message(LogMessageSeverity severity, std::string message, size_t line = 0, const char * file = nullptr);

		void AddSink(std::shared_ptr<LogSink> sink);
		void RemoveSink(std::shared_ptr<LogSink> sink);

	private:
		void MessageImpl(LogMessageData messageData);

		Sinks				_sinks;
	};

	Log & GetLogger();
}
