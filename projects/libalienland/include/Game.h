#pragma once

class TestScene;

class Game
{
public:
	Game();
	~Game();

	void Start(const std::filesystem::path & resourcesDirectory);

private:
	void CreateWindow();
	void CreateTestScene(const std::filesystem::path & resourcesDirectory);

	void PreGameLoop();
	void PostGameLoop();
	void GameLoop();
	void HandleInput();
	void Update(const sf::Time & elapsedTime);
	void Render();

	std::shared_ptr<sf::RenderWindow>	_window;
	std::shared_ptr<TestScene>			_testScene;
	bool								_shouldTerminate = false;
};