#include <filesystem>

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

	InternalCombustionEngine ice;

	Engine* engine = &ice;
	TestStand testStand;
	testStand.Start(engine, ui.GetEnvironmentTemperature(), InitializingFilePath);

	return 0;
}