project(compile_check)

set(EXTERNAL_SDL_ENABLED ON)
include(../../../external.cmake)

add_executable(sdl-check sdl.cpp)
target_link_libraries(sdl-check PRIVATE SDL2-static SDL2main)	# Связывает с исполняемым файлом библиотеки SDL2-static и SDL2main
