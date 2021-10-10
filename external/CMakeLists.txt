if (EXTERNAL_SDL_ENABLED)
	add_subdirectory(sdl)
endif()

if (EXTERNAL_SFML_ENABLED)
	add_subdirectory(sfml)
endif()

if (EXTERNAL_GOOGLETEST_ENABLED)
	add_subdirectory(googletest)
endif()
