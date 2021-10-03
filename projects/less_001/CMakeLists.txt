project(less_001)

include(${EXTERNAL_CMAKE_FILE})	# include(../../external.cmake)

add_executable(less_001 Main.cpp MyString.cpp MyString.h)
