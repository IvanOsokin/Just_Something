#include <filesystem>
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

	TestStand testStand;
	testStand.Start(std::make_shared<InternalCombustionEngine>(), ui.GetEnvironmentTemperature(), InitializingFilePath);

	return 0;
}