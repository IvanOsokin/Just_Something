#include "Imgui/ImguiController.h"

#include "Imgui/ImguiDebugWidget.h"
#include "Imgui/ImguiWidgetBase.h"

ImguiController::ImguiController() = default;
ImguiController::~ImguiController() = default;

void ImguiController::Init(const Settings& settings)
{
	_window = settings.window;

	auto debugWidget = std::make_unique<ImguiDebugWidget>();
	debugWidget->Init();
	_widgets.emplace_back(std::move(debugWidget));
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

void ImguiController::BeginUpdate(float elapsedTime)
{
	auto window = _window.lock();
	if (!window)
	{
		return;
	}

	auto dt = sf::microseconds(static_cast<sf::Int64>(elapsedTime * 1000));
	ImGui::SFML::Update(*window, dt);

	std::for_each(_widgets.begin(), _widgets.end(), [](const ImguiWidgetPtr & widgetPtr)
	{
		widgetPtr->BaseBeginUpdate();
	});
	std::for_each(_widgets.begin(), _widgets.end(), [&](const ImguiWidgetPtr & widgetPtr)
	{
		widgetPtr->BaseUpdate(dt);
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
