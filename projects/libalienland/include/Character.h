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

	float GetDistFromOriginToWeaponTip() const;

	const sf::Texture & GetTexture() const { return _texture; }

private:
	bool LoadTexture(const std::string & characterTexturePath);
		 
	void ProcessKeyboard();
	void ProcessMouse(const sf::Event & event);
		 
	void Move(const sf::Time & elapsedTime);
	void Rotate();

	std::weak_ptr<BulletManager>	_bulletManager;
	std::weak_ptr<GameScene>		_gameScene;

	sf::Texture		_texture;

	sf::Vector2f	_speed;
	sf::Vector2f	_unitSpeedVector;
	sf::Vector2f	_currentCursorPosition;
	float			_baseSpeed = 400.0f;
};
