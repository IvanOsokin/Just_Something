target_sources(${PROJECT_NAME} PRIVATE
	Internal/pch.h
	Log/Log.h
	Log/LogMessageData.h
	Log/LogMessageSeverity.h
	Log/LogSink.h
	Core.h
)

target_precompile_headers(${PROJECT_NAME} PRIVATE Internal/pch.h)
