project(Alienland)

add_executable(${PROJECT_NAME} main.cpp)

target_enable_cpplatest(${PROJECT_NAME})
target_set_binary_output(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/bin)
target_treat_all_warnings_as_error(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
	alienlandlib
	corelib
)
