project(corelib_test)

set(EXTERNAL_GOOGLETEST_ENABLED ON)
include(${EXTERNAL_CMAKE_FILE})

add_executable(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE
	gtest
	gtest_main
	corelib
)

add_subdirectory(Log)
