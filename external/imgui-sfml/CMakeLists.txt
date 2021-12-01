include(FetchContent)

FetchContent_Declare(
	imgui-sfml
	GIT_REPOSITORY git@github.com:eliasdaler/imgui-sfml.git
	GIT_TAG 9cc8c57a4565551087be0d9aeb3ae55490aa1207 # refs/tags/v2.4
)

set(IMGUI_DIR ${EXTERNAL_IMGUI_DIR} CACHE INTERNAL "")
set(SFML_DIR ${EXTERNAL_SFML_DIR}/cmake CACHE INTERNAL "")
set(IMGUI_SFML_IMGUI_DEMO ON CACHE BOOL "IMGUI_SFML_IMGUI_DEMO")
set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "Use find_package to find SFML")

FetchContent_MakeAvailable(imgui-sfml)

unset(SFML_DIR CACHE)
unset(IMGUI_DIR CACHE)
