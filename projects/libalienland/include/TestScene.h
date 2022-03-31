#pragma once

class ImguiController;
class Character;
class Enemy;
class BulletManager;

class TestScene
{
public:
	TestScene();
	~TestScene();

	void Init(std::shared_ptr<sf::RenderWindow> renderWindow, const std::filesystem::path & resourcesDirectory);
	void PreGameLoop();
	void PostGameLoop();

	void PreFrame();
	void ProcessInput(const sf::Event & event);
	void Update(const sf::Time & elapsedTime);
	void Render();
	void PostFrame();

	bool ShouldTerminate() const { return _shouldTerminate; }
		
private:
	void EventLogging(const sf::Event & event);
	void ProcessSceneInput(const sf::Event & event);
	template <typename T>
	void SetInitialPosition(std::shared_ptr<T> object);

	std::unique_ptr<sf::Texture> LoadMapTexture(const std::filesystem::path & resourcesDirectory);
	void RemoveDeadEnemy();
	
	std::weak_ptr<sf::RenderWindow>			_window;
	std::shared_ptr<ImguiController>		_imguiController;
	std::shared_ptr<BulletManager>			_bulletManager;
	std::shared_ptr<Character>				_character;
	std::shared_ptr<Enemy>					_enemy;
	bool									_shouldTerminate = false;

	sf::Texture								_mapTexture;
	sf::Sprite								_mapSprite;
};
