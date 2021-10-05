#include "Game.h"

#include "TestScene.h"

Game::Game()
	: _testScene(std::make_shared<TestScene>())
{
}

Game::~Game() = default;

void Game::Start(const std::filesystem::path & resourcesDirectory)
{
	CreateWindow();
	CreateTestScene();

	GameLoop();
}

void Game::CreateWindow()
{
	const std::string gameTitle = "Alien Land";
	_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), gameTitle);
}

void Game::CreateTestScene()
{
	if (!_window)
	{
		_shouldTerminate = true;
		sf::err() << "Window must be created first." << std::endl;
		return;
	}
	_testScene->Init(_window);
}

void Game::HandleInput()
{
	sf::Event e;
	while (_window->pollEvent(e))
	{
		_testScene->EventLogging(e);
		_testScene->ProcessInput(e);
		_shouldTerminate = _testScene->ShouldTerminate();
	}
}

void Game::Update(sf::Time elapsedTime)
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
	while (!_shouldTerminate)
	{
		const sf::Time elapsedTime = frameClock.getElapsedTime();

		HandleInput();
		Update(elapsedTime);
		Render();

		if (elapsedTime < expectedTps)
		{
			sf::sleep(expectedTps - elapsedTime);
		}
		frameClock.restart();
	}
}