project(compile_check)

set(EXTERNAL_SFML_ENABLED ON)
include(../../../external.cmake)

add_executable(sfml-check sfml.cpp)
target_link_libraries(sfml-check PRIVATE sfml-graphics sfml-system sfml-window)
