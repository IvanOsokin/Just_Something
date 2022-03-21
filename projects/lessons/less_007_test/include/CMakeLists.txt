target_sources(${PROJECT_NAME} PRIVATE
	Engine.h
	InternalCombustionEngine.h
	TestStand.h
	UserInterface.h
	Utils.h

	Internal/Precompile.h
)

target_precompile_headers(${PROJECT_NAME} PRIVATE Internal/Precompile.h)