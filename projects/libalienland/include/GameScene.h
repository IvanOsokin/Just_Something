#pragma once

class ImguiController;
class GameObject;
class BulletManager;
class Bullet;

class GameScene : public std::enable_shared_from_this<GameScene>
{
public:
	GameScene();
	~GameScene();

	void Init(std::shared_ptr<sf::RenderWindow> renderWindow, const std::filesystem::path & resourcesDirectory);
	void PreGameLoop();
	void PostGameLoop();

	void PreFrame();
	void ProcessInput(const sf::Event & event);
	void Update(const sf::Time & elapsedTime);
	void Render();
	void PostFrame();

	void AddBullet(std::shared_ptr<GameScene> gameScene, const sf::Vector2f & curCharPos, float curCharRot, const sf::Vector2f & targetPos);
	bool ShouldTerminate() const { return _shouldTerminate; }
	void SetShouldremoveGameObjectsState(bool shouldRemove) { _shouldRemoveGameObjs = shouldRemove; }
	bool ShouldRemoveGameObjects() const { return _shouldRemoveGameObjs; }
	const sf::IntRect& GetSceneBorder() { return _sceneBorder; }
	const std::vector<std::shared_ptr<GameObject>>& GetGameObjects() { return _gameObjects; }
		
private:
	void AddCharacter(const std::filesystem::path & resourcesDirectory);
	void AddEnemy(const std::filesystem::path & resourcesDirectory);

	void EventLogging(const sf::Event & event);
	void ProcessSceneInput(const sf::Event & event);
	void RemoveMarkedGameObjects();
	void InitSceneBorder();

	void ProcessCollision();

	std::unique_ptr<sf::Texture> LoadMapTexture(const std::filesystem::path & resourcesDirectory);
	
	std::weak_ptr<sf::RenderWindow>				_window;
	std::shared_ptr<ImguiController>			_imguiController;
	std::shared_ptr<BulletManager>				_bulletManager;

	std::vector<std::shared_ptr<GameObject>>	_gameObjects;

	bool										_shouldTerminate = false;
	bool										_shouldRemoveGameObjs = false;

	sf::IntRect									_sceneBorder;
	sf::Texture									_mapTexture;
	sf::Sprite									_mapSprite;
};
