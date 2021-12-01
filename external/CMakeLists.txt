# Config
option(EXTERNAL_DEBUG_FETCH_CONTENT OFF)
if (EXTERNAL_DEBUG_FETCH_CONTENT)
	set(FETCHCONTENT_QUIET OFF)
endif()

# Projects:
if (EXTERNAL_SDL_ENABLED)
	add_subdirectory(sdl)
endif()

if (EXTERNAL_SFML_ENABLED)
	add_subdirectory(sfml)
endif()

if (EXTERNAL_GOOGLETEST_ENABLED)
	add_subdirectory(googletest)
endif()

if (NOT TARGET corelib)
	add_subdirectory(corelib)
endif()

if (EXTERNAL_IMGUI_ENABLED)
	add_subdirectory(imgui)
endif()

if (EXTERNAL_SFML_ENABLED AND EXTERNAL_IMGUI_ENABLED)
	add_subdirectory(imgui-sfml)
endif()
