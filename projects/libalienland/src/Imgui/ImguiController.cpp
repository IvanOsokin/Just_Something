#include "Imgui/ImguiController.h"

#include "Imgui/ImguiWidgetBase.h"

ImguiController::ImguiController() = default;
ImguiController::~ImguiController() = default;

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

	std::for_each(_widgets.begin(), _widgets.end(), [](const ImguiWidgetPtr & widgetPtr)
	{
		widgetPtr->BaseBeginUpdate();
	});
	std::for_each(_widgets.begin(), _widgets.end(), [&](const ImguiWidgetPtr & widgetPtr)
	{
		widgetPtr->BaseUpdate(elapsedTime);
	});
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

void ImguiController::EndFrame()
{
	std::for_each(_widgets.begin(), _widgets.end(), [&](const ImguiWidgetPtr & widgetPtr)
	{
		widgetPtr->BaseEndFrame();
	});
}

void ImguiController::CleanUp()
{
	ImGui::SFML::Shutdown();
}

void ImguiController::BeginFrame()
{
	std::for_each(_widgets.begin(), _widgets.end(), [&](const ImguiWidgetPtr & widgetPtr)
	{
		widgetPtr->BaseBeginFrame();
	});
}

void ImguiController::EndUpdate()
{
	std::for_each(_widgets.begin(), _widgets.end(), [&](const ImguiWidgetPtr & widgetPtr)
	{
		widgetPtr->BaseEndUpdate();
	});
	ImGui::EndFrame();
}
