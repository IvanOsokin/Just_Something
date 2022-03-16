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

	auto ice = std::make_shared<InternalCombustionEngine>();
	ice->Init(ui.GetEnvironmentTemperature(), InitializingFilePath);

	TestStand testStand;
	testStand.Start(ice);

	return 0;
}