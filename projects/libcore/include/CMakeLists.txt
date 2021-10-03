target_sources(${PROJECT_NAME} PRIVATE
	Internal/pch.h
	Log/DebuggerDisplaySink.h
	Log/FileLogSink.h
	Log/Log.h
	Log/LogMessageData.h
	Log/LogMessageSeverity.h
	Log/LogSink.h
	Log/LogUtils.h
	Core.h
)

target_precompile_headers(${PROJECT_NAME} PRIVATE Internal/pch.h)
