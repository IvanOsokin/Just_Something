#pragma once
#include "ImguiWidgetBase.h"

class FrameProcessor;

class ImguiDebugWidget : public ImguiWidgetBase
{
public:
	ImguiDebugWidget();
	~ImguiDebugWidget();

	void Init();

	void BeginFrame() override;
	void Update(sf::Time elapsedTime) override;
	void EndFrame() override;

private:

	std::unique_ptr<FrameProcessor>		_fpsCounter;
};
