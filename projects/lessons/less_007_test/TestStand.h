#pragma once

#include "Engine.h"

class Engine;

class TestStand
{
public:
	void Start(Engine* testEngine, double environmentTemp, const std::filesystem::path& InitializingFilePath);

private:
	void Init(Engine* testEngine);
	void MainCycle();
	void DisplayResult();

	Engine* _testEngine = nullptr;

	double _duration = 0.0;
	bool _shouldStopStand = false;
};