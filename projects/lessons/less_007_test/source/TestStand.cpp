#include "TestStand.h"
#include "Engine.h"

void TestStand::Start(std::shared_ptr<Engine> testEngine)
{
	if (!testEngine)
	{
		std::cout << "Could not get an engine for testing";
		return;
	}

	testEngine->Start();

	MainCycle(testEngine);
}

void TestStand::MainCycle(std::shared_ptr<Engine> testEngine)
{
	const double timeSegment = 0.01;
	const int examineDuration = 60;

	for (; _workTime < examineDuration; _workTime += timeSegment)
	{
		if (testEngine->IsOverheated())
		{			
			_wasInterrupted = true;
			break;
		}

		testEngine->MainCycle(timeSegment);
	}
}
