macro(target_enable_cpplatest project)
	if(MSVC)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
	else()
		target_compile_features(${project} PRIVATE cxx_std_20)
	endif()
endmacro()

function(target_set_binary_output project dir)
	set_target_properties(${project} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${dir})
	set_target_properties(${project} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${dir})
	set_target_properties(${project} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${dir})
	set_target_properties(${project} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${dir})
	set_target_properties(${project} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${dir})
endfunction()

function(target_treat_all_warnings_as_error project)
	target_compile_options(${project} PRIVATE
		$<$<CXX_COMPILER_ID:Clang>:-Werror>
		$<$<CXX_COMPILER_ID:MSVC>:-W4 -WX /permissive->
	)
	target_compile_definitions(${project} PRIVATE
		$<$<BOOL:${WIN32}>:_CRT_SECURE_NO_WARNINGS>
	)
endfunction()

macro(target_enable_timetrace project)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_compile_options(${project} PRIVATE "-ftime-trace")
	else()
		message(FATAL_ERROR "Option time-trace enabled only with clang compiler")
	endif()
endmacro()
