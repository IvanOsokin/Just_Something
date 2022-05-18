project(alienlandlib)

set(EXTERNAL_SFML_ENABLED ON)
set(EXTERNAL_IMGUI_ENABLED ON)
include(${EXTERNAL_CMAKE_FILE})
include(${CMAKE_HELPERS_FILE_DIR}/config.cmake)

add_library(${PROJECT_NAME} STATIC)
add_subdirectory(include)
add_subdirectory(src)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_enable_cpplatest(${PROJECT_NAME})
target_treat_all_warnings_as_error(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC
	sfml-graphics
	sfml-system
	sfml-window
	ImGui-SFML
	corelib
)

option(PROJECTS_ALIENLANDLIB_ENABLE_TESTS OFF)
if (PROJECTS_ALIENLANDLIB_ENABLE_TESTS)
	add_subdirectory(tests)
endif()

option(PROJECTS_ALIENLANDLIB_ENABLE_TIMETRACE OFF)
if (PROJECTS_ENABLE_TIMETRACE)
	enable_timetrace()
endif()
