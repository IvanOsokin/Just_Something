#include "Game.h"

#include "TestScene.h"

Game::Game()
	: _testScene(std::make_shared<TestScene>())
{
}

Game::~Game() = default;

void Game::Start(const std::filesystem::path & resourcesDirectory)
{
	AssertVar std::error_code ec;
	Assert(std::filesystem::is_directory(resourcesDirectory, ec));

	CreateWindow();
	CreateTestScene(resourcesDirectory);

	GameLoop();
}

void Game::CreateWindow()
{
	const std::string gameTitle = "Alien Land";
	_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), gameTitle);
}

void Game::CreateTestScene(const std::filesystem::path & resourcesDirectory)
{
	if (!Verify2(_window, "Window must be created first."))
	{
		_shouldTerminate = true;
		return;
	}
	_testScene->Init(_window, resourcesDirectory);
}

void Game::HandleInput()
{
	sf::Event e;
	while (_window->pollEvent(e))
	{
		_testScene->ProcessInput(e);
		_shouldTerminate = _testScene->ShouldTerminate();
	}
}

void Game::Update(const sf::Time & elapsedTime)
{
	_testScene->Update(elapsedTime);
}

void Game::Render()
{
	_window->clear();
	_testScene->Render();
	_window->display();
}

void Game::GameLoop()
{
	const size_t expectedFps = 60;
	const auto expectedTps = sf::milliseconds(1000 / expectedFps);

	sf::Clock frameClock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (!_shouldTerminate)
	{
		timeSinceLastUpdate += frameClock.restart();

		while (timeSinceLastUpdate >= expectedTps)
		{
			timeSinceLastUpdate -= expectedTps;
			HandleInput();
			Update(expectedTps);
		}

		Render();
	}
}