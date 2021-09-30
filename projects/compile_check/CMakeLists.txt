project(compile_check)

set(EXTERNAL_SDL_ENABLED ON)
set(EXTERNAL_SFML_ENABLED ON)
include(../../external.cmake)

add_executable(sdl-check sdl.cpp)
target_link_libraries(sdl-check PRIVATE SDL2-static SDL2main)

add_executable(sfml-check sfml.cpp)
target_link_libraries(sfml-check PRIVATE sfml-graphics sfml-system sfml-window)
