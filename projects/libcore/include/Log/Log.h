#pragma once

#define LOG_MESSAGE_IMPL(severity, msg) \
	Core::Log::Instance().Message(severity, (msg), __LINE__, __FILE__);

#define LOG_DEBUG(msg) LOG_MESSAGE_IMPL(Core::LogMessageSeverity::Debug, msg)
#define LOG_INFO(msg) LOG_MESSAGE_IMPL(Core::LogMessageSeverity::Info, msg)
#define LOG_WARNING(msg) LOG_MESSAGE_IMPL(Core::LogMessageSeverity::Warning, msg)
#define LOG_ERROR(msg) LOG_MESSAGE_IMPL(Core::LogMessageSeverity::Error, msg)
#define LOG_FATAL_ERROR(msg) LOG_MESSAGE_IMPL(Core::LogMessageSeverity::FatalError, msg)

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
