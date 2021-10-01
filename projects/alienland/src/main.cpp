#include "Game.h"

int main(int /*argc*/, char **argv)
{
	auto executableName = std::filesystem::path(argv[0]);
	auto executableDirectory = executableName.parent_path();
	auto resourcesDirectory = executableDirectory / "resources";
	
	Game game;
	game.Start(resourcesDirectory);
	return 0;
}
