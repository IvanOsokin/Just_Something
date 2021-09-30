include(FetchContent)

FetchContent_Declare(
	sdllib
	GIT_REPOSITORY git@github.com:libsdl-org/SDL.git
	GIT_TAG 25f9ed87ff6947d9576fc9d79dee0784e638ac58 # refs/tags/release-2.0.16
)
set(SDL_SHARED OFF CACHE INTERNAL "")
set(SDL_AUDIO OFF CACHE INTERNAL "")
set(SDL_DLOPEN OFF CACHE INTERNAL "")
set(SDL_HAPTIC OFF CACHE INTERNAL "")
set(SDL_JOYSTIK OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(sdllib)
