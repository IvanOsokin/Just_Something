project(less_007_test)

include(${CMAKE_HELPERS_FILE_DIR}/config.cmake)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(include)
add_subdirectory(source)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_enable_cpplatest(${PROJECT_NAME})
target_treat_all_warnings_as_error(${PROJECT_NAME})