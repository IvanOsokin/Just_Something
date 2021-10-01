#pragma once

class Character;
class Enemy;

class TestScene
{
public:
	TestScene();
	~TestScene();

	void Init(sf::RenderWindow & renderWindow);

	void ProcessInput(const sf::Event & event);
	void Update(sf::Time elapsedTime);
	void Render();

	bool ShouldTerminate() const { return _shouldTerminate; }

private:
	void ProcessSceneInput(const sf::Event & event);
	bool TerminateIfEmptyWindow();
	
	std::unique_ptr<Character>		_character;
	std::unique_ptr<Enemy>			_enemy;
	bool							_shouldTerminate = false;
	sf::RenderWindow *				_window = nullptr;
};
