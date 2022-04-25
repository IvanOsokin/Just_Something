#include "Game.h"

#include "GameScene.h"

Game::Game()
	: _gameScene(std::make_shared<GameScene>())
{
}

Game::~Game() = default;

void Game::Start(const std::filesystem::path & resourcesDirectory)
{
	AssertVar std::error_code ec;
	Assert(std::filesystem::is_directory(resourcesDirectory, ec));

	CreateWindow();
	CreateGameScene(resourcesDirectory);

	PreGameLoop();
	GameLoop();
	PostGameLoop();
}

void Game::CreateWindow()
{
	const std::string gameTitle = "Alien Land";
	_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), gameTitle);
}

void Game::CreateGameScene(const std::filesystem::path & resourcesDirectory)
{
	if (!Verify2(_window, "Window must be created first."))
	{
		_shouldTerminate = true;
		return;
	}
	_gameScene->Init(_window, resourcesDirectory);
}

void Game::PreGameLoop()
{
	_gameScene->PreGameLoop();
}

void Game::PostGameLoop()
{
	_gameScene->PostGameLoop();
}

void Game::PreFrame()
{
	_gameScene->PreFrame();
}

void Game::HandleInput()
{
	sf::Event e;
	while (_window->pollEvent(e))
	{
		_gameScene->ProcessInput(e);
		_shouldTerminate = _gameScene->ShouldTerminate();
	}
}

void Game::Update(const sf::Time & elapsedTime)
{
	_gameScene->Update(elapsedTime);
}

void Game::Render()
{
	_window->clear();
	_gameScene->Render();
	_window->display();
}

void Game::PostFrame()
{
	_gameScene->PostFrame();
}

void Game::GameLoop()
{
	const size_t expectedFps = 60;
	const auto expectedTps = sf::milliseconds(1000 / expectedFps);

	const auto deltaTime = sf::microseconds(1000);

	sf::Clock frameClock;
	// Guarantee at least one update before render.
	sf::Time  timeSinceLastUpdate = deltaTime;

	while (!_shouldTerminate)
	{
		timeSinceLastUpdate += frameClock.restart();

		PreFrame();
		HandleInput();
		while (timeSinceLastUpdate >= deltaTime)
		{
			timeSinceLastUpdate -= deltaTime;
			Update(deltaTime);
		}
		
		Render();
		PostFrame();

		const auto elapsedTime = frameClock.getElapsedTime();
		if (elapsedTime < expectedTps)
		{
			sf::sleep(expectedTps - elapsedTime);
		}
	}
}
