project(Alienland)

set(EXTERNAL_SFML_ENABLED ON)
include(${EXTERNAL_CMAKE_FILE})
include(cmake/config.cmake)

add_executable(${PROJECT_NAME})
add_subdirectory(include)
add_subdirectory(src)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-system sfml-window)
target_enable_cpplatest(${PROJECT_NAME})
