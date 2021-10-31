#include "Game.h"
#include "Log/DebuggerDisplaySink.h"
#include "Log/FileLogSink.h"

int main(int /*argc*/, char **argv)
{
	auto executableName = std::filesystem::path(argv[0]);
	auto executableDirectory = executableName.parent_path();
	auto resourcesDirectory = executableDirectory / "resources";

	Core::GetLogger().AddSink(std::make_shared<Core::DebuggerDisplaySink>());

	auto fileLogSink = std::make_shared<Core::FileLogSink>();
	fileLogSink->Init(executableDirectory / "Alienland.log");
	Core::GetLogger().AddSink(fileLogSink);

	Game game;
	game.Start(resourcesDirectory);
	return 0;
}
