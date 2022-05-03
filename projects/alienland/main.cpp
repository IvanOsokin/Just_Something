#include <filesystem>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "SfmlGameLoopDelegate.h"
#include "Log/DebuggerDisplaySink.h"
#include "Log/FileLogSink.h"
#include "Log/Log.h"

int main(int /*argc*/, char **argv)
{
	auto executableName = std::filesystem::path(argv[0]);
	auto executableDirectory = executableName.parent_path();
	auto resourcesDirectory = executableDirectory / "resources";

	Core::GetLogger().AddSink(std::make_shared<Core::DebuggerDisplaySink>());

	auto fileLogSink = std::make_shared<Core::FileLogSink>();
	fileLogSink->Init(executableDirectory / "Alienland.log");
	Core::GetLogger().AddSink(fileLogSink);

	const std::string gameTitle = "Alien Land";
	auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), gameTitle);
	sf::Time deltaTime = sf::microseconds(1000);
	const int requestedFps = 60;
	std::unique_ptr<GameLoopDelegate> delegate = std::make_unique<SfmlGameLoopDelegate>(window, resourcesDirectory, deltaTime, requestedFps);

	Game game(std::move(delegate));
	game.Start();

	return 0;
}
