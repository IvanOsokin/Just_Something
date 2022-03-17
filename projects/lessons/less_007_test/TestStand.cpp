#include <filesystem>
#include <iostream>

#include "TestStand.h"
#include "Utils.h"

void TestStand::Start(std::shared_ptr<Engine> testEngine)
{
	if (!testEngine)
	{
		std::cout << "Could not get an engine for testing";
		return;
	}

	testEngine->Start();

	MainCycle(testEngine);

	Utils::DisplayResult(_wasInterrupted, _workTime);
}

void TestStand::MainCycle(std::shared_ptr<Engine> testEngine)
{
	const double timeSegment = 0.01;
	const int examineDuration = 60;

	for (; _workTime < examineDuration; _workTime += timeSegment)
	{
		if (testEngine->IsOverheated())
		{
			if (_workTime - 0 > timeSegment)	//Checks if the engine is overheated at the beginning
			{
				_workTime -= timeSegment;
			}
			
			_wasInterrupted = true;
			break;
		}

		testEngine->MainCycle(timeSegment);
	}
}
