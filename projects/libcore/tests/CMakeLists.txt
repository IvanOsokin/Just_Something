project(corelib_test)

set(EXTERNAL_GOOGLETEST_ENABLED ON)
include(${EXTERNAL_CMAKE_FILE})

add_executable(testsample sample.cpp)
target_link_libraries(testsample gtest gmock)
