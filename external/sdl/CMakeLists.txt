include(FetchContent) #Включает модуль для заполнения/извлечения контента в процессе конфигурации

FetchContent_Declare( #Функция записи опций, которые описывают, как необходимо заполнять контент FetchContent_Declare(<name> <contentOptions>...)
	sdllib
	GIT_REPOSITORY git@github.com:libsdl-org/SDL.git
	GIT_TAG 25f9ed87ff6947d9576fc9d79dee0784e638ac58 # refs/tags/release-2.0.16
)
set(SDL_SHARED OFF CACHE INTERNAL "")	#Создание переменной SDL_SHARED со значением OFF (также устанваливает кэш перменной, как - не знаю)
set(SDL_AUDIO OFF CACHE INTERNAL "")
set(SDL_DLOPEN OFF CACHE INTERNAL "")
set(SDL_HAPTIC OFF CACHE INTERNAL "")
set(SDL_JOYSTIK OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(sdllib)	#Делает добавленный/скаченный проект доступным во время конфигурации проекта
