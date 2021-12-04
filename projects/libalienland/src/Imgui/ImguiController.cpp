#include "Imgui/ImguiController.h"

void ImguiController::Init(const Settings& settings)
{
	_window = settings.window;
}

void ImguiController::Prepare()
{
	auto window = _window.lock();
	if (!window)
	{
		return;
	}
	ImGui::SFML::Init(*window);
}

void ImguiController::ProcessInput(const sf::Event& event)
{
	ImGui::SFML::ProcessEvent(event);
}

void ImguiController::BeginUpdate(sf::Time elapsedTime)
{
	auto window = _window.lock();
	if (!window)
	{
		return;
	}
	ImGui::SFML::Update(*window, elapsedTime);
}

void ImguiController::Render()
{
	auto window = _window.lock();
	if (!window)
	{
		return;
	}
	ImGui::SFML::Render(*window);
}

void ImguiController::CleanUp()
{
	ImGui::SFML::Shutdown();
}

void ImguiController::EndUpdate()
{
	ImGui::EndFrame();
}
