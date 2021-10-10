project(corelib)

include(${CMAKE_HELPERS_FILE_DIR}/config.cmake)

add_library(${PROJECT_NAME} STATIC)
add_subdirectory(include)
add_subdirectory(src)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_enable_cpplatest(${PROJECT_NAME})
target_treat_all_warnings_as_error(${PROJECT_NAME})

option(PROJECTS_CORELIB_TEST_ENABLED OFF)
if (PROJECTS_CORELIB_TEST_ENABLED)
	add_subdirectory(tests)
endif()
