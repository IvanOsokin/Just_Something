#include "Internal/pch.h"
#include "SfmlGameLoopDelegate.h"

SfmlGameLoopDelegate::SfmlGameLoopDelegate(std::shared_ptr<sf::RenderWindow> window, const std::filesystem::path & resourcesDirectory, const sf::Time & deltaTime, int requestedFps)
	: _window(window)
	, _gameScene(std::make_shared<GameScene>())
	, _deltaTime(deltaTime)
	, _requestedFps(requestedFps)
{
	InitializeGameScene(resourcesDirectory);
}

int SfmlGameLoopDelegate::RequestedFps() const
{
	return _requestedFps;
}

void SfmlGameLoopDelegate::PreGameLoop()
{
	_gameScene->PreGameLoop();
}

void SfmlGameLoopDelegate::PostGameLoop()
{
	_gameScene->PreGameLoop();
}

void SfmlGameLoopDelegate::PreFrame()
{
	_gameScene->PreFrame();
}

void SfmlGameLoopDelegate::PostFrame()
{
	_gameScene->PostFrame();
}

void SfmlGameLoopDelegate::Update()
{
	_gameScene->Update(_deltaTime);
}

void SfmlGameLoopDelegate::Input()
{
	sf::Event e;
	while (_window->pollEvent(e))
	{
		_gameScene->ProcessInput(e);
		_shouldTerminate = _gameScene->ShouldTerminate();
	}
}

void SfmlGameLoopDelegate::Render()
{
	_window->clear();
	_gameScene->Render();
	_window->display();
}

bool SfmlGameLoopDelegate::ShouldTerminate() const
{
	return _shouldTerminate;
}

void SfmlGameLoopDelegate::InitializeGameScene(const std::filesystem::path & resourcesDirectory)
{
	if (!Verify2(_window, "Window must be created first."))
	{
		_shouldTerminate = true;
		return;
	}

	AssertVar std::error_code ec;
	Assert(std::filesystem::is_directory(resourcesDirectory, ec));

	_gameScene->Init(_window, resourcesDirectory);
}
