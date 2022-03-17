#include <filesystem>
#include <iostream>
#include <memory>

#include "UserInterface.h"
#include "InternalCombustionEngine.h"
#include "TestStand.h"

int main(int argc, char** argv)
{
	auto executableName = std::filesystem::path(argv[0]);
	auto InitializingFilePath = executableName.parent_path();
	InitializingFilePath /= "EngineParameters.ini";

	UserInterface ui;
	ui.ProcessInput();

	auto ice = std::make_shared<InternalCombustionEngine>();
	if (!(ice->Init(ui.GetEnvironmentTemperature(), InitializingFilePath)))
	{
		std::cout << "The engine examined parameters hasn't been initialized";
		return -1;
	}

	TestStand testStand;
	testStand.Start(ice);

	return 0;
}