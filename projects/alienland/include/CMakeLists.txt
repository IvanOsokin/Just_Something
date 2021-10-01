target_sources(${PROJECT_NAME} PRIVATE
	internal/pch.h
)

target_precompile_headers(${PROJECT_NAME} PRIVATE internal/pch.h)
