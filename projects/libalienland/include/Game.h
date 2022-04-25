#pragma once

class GameScene;

class Game
{
public:
	Game();
	~Game();

	void Start(const std::filesystem::path & resourcesDirectory);

private:
	void CreateWindow();
	void CreateGameScene(const std::filesystem::path & resourcesDirectory);

	void PreGameLoop();
	void GameLoop();
	void PostGameLoop();

	void PreFrame();
	void HandleInput();
	void Update(const sf::Time & elapsedTime);
	void Render();
	void PostFrame();

	std::shared_ptr<sf::RenderWindow>	_window;
	std::shared_ptr<GameScene>			_gameScene;
	bool								_shouldTerminate = false;
};