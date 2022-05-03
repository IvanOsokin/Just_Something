#include "Game.h"
#include "SfmlGameLoopDelegate.h"

Game::Game(std::unique_ptr<GameLoopDelegate> delegate)
	: _delegate(std::move(delegate))
{
}

Game::~Game() = default;

void Game::Start()
{
	_delegate->PreGameLoop();
	GameLoop();
	_delegate->PostGameLoop();
}

void Game::GameLoop()
{
	const sf::Int32 expectedFps = _delegate->RequestedFps();
	const auto expectedTps = sf::milliseconds(1000 / expectedFps);

	const auto deltaTime = sf::microseconds(1000);

	sf::Clock frameClock;
	// Guarantee at least one update before render.
	sf::Time  timeSinceLastUpdate = deltaTime;

	while (!_delegate->ShouldTerminate())
	{
		timeSinceLastUpdate += frameClock.restart();

		_delegate->PreFrame();
		_delegate->Input();
		while (timeSinceLastUpdate >= deltaTime)
		{
			timeSinceLastUpdate -= deltaTime;
			_delegate->Update();
		}
		_delegate->Render();
		_delegate->PostFrame();

		const auto elapsedTime = frameClock.getElapsedTime();
		if (elapsedTime < expectedTps)
		{
			sf::sleep(expectedTps - elapsedTime);
		}
	}
}
