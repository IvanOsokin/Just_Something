#include <filesystem>
#include <iostream>

#include "TestStand.h"

TestStand::TestStand()
	: _testEngine(std::make_shared<Engine>())
{}

void TestStand::Start(std::shared_ptr<InternalCombustionEngine> testEngine, double environmentTemp, const std::filesystem::path& InitializingFilePath)
{
	Init(testEngine);

	_testEngine->Start(environmentTemp, InitializingFilePath);

	MainCycle();

	DisplayResult();
}

void TestStand::Init(std::shared_ptr<InternalCombustionEngine> testEngine)
{
	_testEngine = testEngine;
}

void TestStand::MainCycle()
{
	const double timeSegment = 0.01;
	const int examineDuration = 60;

	for (; _duration < examineDuration; _duration += timeSegment)
	{
		if (_testEngine->IsOverheated())
		{
			_shouldStopStand = true;
			
			return;
		}

		_testEngine->MainCycle(timeSegment);
	}
}

void TestStand::DisplayResult()
{
	if (_shouldStopStand)
	{
		std::cout << _duration << " seconds since the engine has started till overheated" << std::endl;
	}
	else
	{
		std::cout << "The engine examined was not overheated" << std::endl;
	}

	std::cin.get();
}
