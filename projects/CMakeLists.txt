cmake_minimum_required(VERSION 3.18)
project("Root Project")

# Устанваливает заданный путь в переменную EXTERNAL_CMAKE_FILE_NAME
# Получает содержимое файла, расположенного по реальному пути из перменной EXTERNAL_CMAKE_FILE_NAME, в кэш перменной EXTERNAL_CMAKE_FILE
get_filename_component(EXTERNAL_CMAKE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../external.cmake" REALPATH CACHE)

get_filename_component(CMAKE_HELPERS_FILE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/." DIRECTORY CACHE)

add_subdirectory(compile_check)
add_subdirectory(less_001)
add_subdirectory(less_002)
add_subdirectory(less_003)
add_subdirectory(less_004)

add_subdirectory(libcore)
add_subdirectory(alienland)
