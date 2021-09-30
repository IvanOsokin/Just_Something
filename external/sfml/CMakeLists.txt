include(FetchContent)

FetchContent_Declare(
	sfmllib
	GIT_REPOSITORY git@github.com:SFML/SFML.git
	GIT_TAG 2f11710abc5aa478503a7ff3f9e654bd2078ebab # refs/tags/2.5.1
)

set(SFML_BUILD_AUDIO OFF CACHE INTERNAL "")
set(SFML_STATIC_LIBRARIES ON CACHE INTERNAL "")
set(BUILD_SHARED_LIBS OFF)
FetchContent_MakeAvailable(sfmllib)
