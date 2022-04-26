#pragma once

#include "GameObject.h"

// Добавить описание класса
class BulletManager;
class GameScene;

class Character : public GameObject
{
public:
	~Character() = default;
	void Init(const std::filesystem::path & resourcesDirectory, std::shared_ptr<GameScene> gameScene, std::shared_ptr<BulletManager> bulletManager);

	void ProcessInput(const sf::Event & event) override;
	void Update(const sf::Time & elapsedTime) override;
	void ProcessCollision() override;

	const sf::Vector2f& GetPosition() const { return _pos; }
	void SetPosition(const sf::Vector2f pos) { _pos = pos; }
	float GetDistFromOriginToWeaponTip() const;

	const sf::Sprite & GetSprite() const { return _sprite; }

private:
	bool LoadTexture(const std::string & characterTexturePath);
		 
	void ProcessKeyboard();
	void ProcessMouse(const sf::Event & event);
		 
	void Move(const sf::Time & elapsedTime);
	void Rotate();

	std::weak_ptr<BulletManager>	_bulletManager;
	std::weak_ptr<GameScene>		_gameScene;

	sf::Texture		_texture;
	sf::Sprite		_sprite;
	
	sf::Vector2f	_pos;
	sf::Vector2f	_speed;
	sf::Vector2f	_unitSpeedVector;
	sf::Vector2f	_currentCursorPosition;
	float			_baseSpeed = 400.0f;
};

/*

class GameLoopDelegate
{
public:
	virtual int64_t RequestedFps() const = 0;
	
	virtual void PreGameLoop() = 0;
	virtual void PostGameLoop() = 0;
	
	virtual void PreFrame() = 0;
	virtual void PostFrame() = 0;
	
	virtual void Update() = 0;
	virtual void Input() = 0;
	virtual void Render() = 0;
	
	virtual bool ShouldTerminate() const = 0;
};

class Game
{
public:
	Game(GameLoopDelegate & delegate);

	GameLoopDelegate & _delegate;
	

	void GameLoop()
	{
		const size_t expectedFps = _delegate.RequestedFps();
		const auto expectedTps = sf::milliseconds(1000 / expectedFps);
		const auto deltaTime = sf::microseconds(1000);

		sf::Clock frameClock;
		// Guarantee at least one update before render.
		sf::Time  timeSinceLastUpdate = deltaTime;
		
		_delegate.PreGameLoop();
		while (!_delegate.ShouldTerminate())
		{
			timeSinceLastUpdate += frameClock.restart();

			_delegate.PreFrame();
			_delegate.Input();
			_delegate.Update();
			_delegate.Render();
			_delegate.PostFrame();

			const auto elapsedTime = frameClock.getElapsedTime();
			if (elapsedTime < expectedTps)
			{
				sf::sleep(expectedTps - elapsedTime);
			}
		}
		_delegate.PostGameLoop();
	}
};

class SfmlGameLoopDelegate : public GameLoopDelegate
{
	SfmlGameLoopDelegate(sf::RenderWindow & window);
	sf::RenderWindow &	_window;

	void Render() override
	{
		for (auto & object : _scene.GetObjects())
		{
			_window.draw(object);
		}
		
	}
};

*/