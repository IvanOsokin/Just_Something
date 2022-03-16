#pragma once

#include <memory>

#include "Engine.h"

class TestStand
{
public:
	void Start(std::shared_ptr<Engine> testEngine);

private:
	void MainCycle(std::shared_ptr<Engine> testEngine);

	double _workTime = 0.0;
	bool _wasInterrupted = false;
};