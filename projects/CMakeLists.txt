cmake_minimum_required(VERSION 3.18)
project("Root Project")

set(EXTERNAL_CMAKE_FILE_NAME "${CMAKE_CURRENT_SOURCE_DIR}/../external.cmake")		# Устанваливает заданный путь в переменную EXTERNAL_CMAKE_FILE_NAME
get_filename_component(EXTERNAL_CMAKE_FILE ${EXTERNAL_CMAKE_FILE_NAME} REALPATH CACHE)	# Получает содержимое файла, расположенного по реальному пути из перменной EXTERNAL_CMAKE_FILE_NAME,
											# в кэш перменной EXTERNAL_CMAKE_FILE
add_subdirectory(compile_check)
add_subdirectory(less_001)
add_subdirectory(alienland)
