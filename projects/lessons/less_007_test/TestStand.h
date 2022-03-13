#pragma once

#include <memory>

#include "Engine.h"
#include "InternalCombustionEngine.h"

class Engine;

class TestStand
{
public:
	TestStand();

	void Start(std::shared_ptr<InternalCombustionEngine> testEngine, double environmentTemp, const std::filesystem::path& InitializingFilePath);

private:
	void Init(std::shared_ptr<InternalCombustionEngine> testEngine);
	void MainCycle();
	void DisplayResult();

	std::shared_ptr<Engine> _testEngine;

	double _duration = 0.0;
	bool _shouldStopStand = false;
};