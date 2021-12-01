include(FetchContent)

FetchContent_Declare(
	imgui
	GIT_REPOSITORY git@github.com:ocornut/imgui.git
	GIT_TAG 55d35d8387c15bf0cfd71861df67af8cfbda7456 # refs/tags/v1.85
)

FetchContent_MakeAvailable(imgui)

set(EXTERNAL_IMGUI_DIR ${imgui_SOURCE_DIR} CACHE PATH "Path to imgui directory")
