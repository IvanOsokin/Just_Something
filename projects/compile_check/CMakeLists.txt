option(PROJECTS_COMPILE_CHECK_SDL OFF)
option(PROJECTS_COMPILE_CHECK_SFML OFF)

if (PROJECTS_COMPILE_CHECK_SDL)
	add_subdirectory(sdl)
endif()

if (PROJECTS_COMPILE_CHECK_SFML)
	add_subdirectory(sfml)
endif()
