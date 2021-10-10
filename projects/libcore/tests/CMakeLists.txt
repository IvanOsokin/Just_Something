project(corelib_test)

set(EXTERNAL_GOOGLETEST_ENABLED ON)
include(${EXTERNAL_CMAKE_FILE})

add_executable(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE
	gtest
	gtest_main
	corelib
)
target_precompile_headers(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include/Internal/pch.h")

add_subdirectory(src)
add_subdirectory(include)
