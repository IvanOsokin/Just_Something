#pragma once

#include "GameLoopDelegate.h"
#include "GameScene.h"

class SfmlGameLoopDelegate : public GameLoopDelegate
{
public:
	SfmlGameLoopDelegate(std::shared_ptr<sf::RenderWindow> window, const std::filesystem::path & resourcesDirectory, const sf::Time & deltaTime, int requestedFps);
	~SfmlGameLoopDelegate() override {};

	int RequestedFps() const override;

	void PreGameLoop() override;
	void PostGameLoop() override;
	
	void PreFrame() override;
	void PostFrame() override;
	
	void Update() override;
	void Input() override;
	void Render() override;
	
	bool ShouldTerminate() const override;

private:
	void InitializeGameScene(const std::filesystem::path & resourcesDirectory);

	std::shared_ptr<sf::RenderWindow>	_window;
	std::shared_ptr<GameScene>			_gameScene;

	sf::Time							_deltaTime;

	int									_requestedFps = 0;
	bool								_shouldTerminate = false;
};