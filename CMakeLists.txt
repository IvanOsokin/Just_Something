add_subdirectory(external)

project(test)
add_executable(${PROJECT_NAME} main.cpp)
if (NOT TARGET SDL2)
	message(FATAL_ERROR "SDL2 not found")
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2)
