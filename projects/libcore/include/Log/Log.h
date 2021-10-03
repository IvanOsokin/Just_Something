#pragma once

#define LOG_DEBUG(msg) \
	Core::Log::Instance().Message(Core::LogMessageSeverity::Debug, (msg), __LINE__, __FILE__);
#define LOG_INFO(msg) \
	Core::Log::Instance().Message(Core::LogMessageSeverity::Info, (msg), __LINE__, __FILE__);
#define LOG_WARNING(msg) \
	Core::Log::Instance().Message(Core::LogMessageSeverity::Warning, (msg), __LINE__, __FILE__);
#define LOG_ERROR(msg) \
	Core::Log::Instance().Message(Core::LogMessageSeverity::Error, (msg), __LINE__, __FILE__);
#define LOG_FATAL_ERROR(msg) \
	Core::Log::Instance().Message(Core::LogMessageSeverity::FatalError, (msg), __LINE__, __FILE__);

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
