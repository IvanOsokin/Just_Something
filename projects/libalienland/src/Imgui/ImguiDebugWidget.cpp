#include "Imgui/ImguiDebugWidget.h"
#include "Imgui/Impl/FrameProcessor.h"

ImguiDebugWidget::ImguiDebugWidget()
	: _fpsCounter(std::make_unique<FrameProcessor>())
{
}

ImguiDebugWidget::~ImguiDebugWidget() = default;

void ImguiDebugWidget::Init()
{
	FrameProcessor::Settings settings;
	settings.framesHistoryLength = 300;
	_fpsCounter->Init(settings);
}

void ImguiDebugWidget::BeginFrame()
{
	_fpsCounter->FrameStart();
}

void ImguiDebugWidget::Update(sf::Time /*elapsedTime*/)
{
	ImGui::Text("FPS: %.2f", _fpsCounter->CalcFramesPerSecond());

	const int64_t ms = std::chrono::duration_cast<std::chrono::milliseconds>(_fpsCounter->CalcTimePerFrame()).count();
	ImGui::Text("TPS: %.2f", ms / 1000.f);
}

void ImguiDebugWidget::EndFrame()
{
	_fpsCounter->FrameEnd();
}
