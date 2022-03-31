#pragma once

#include "GameObject.h"

// Добавить описание класса
class BulletManager;

class Character : public GameObject
{
public:
	Character() {};
	~Character() = default;
	void Init(const std::filesystem::path & resourcesDirectory, std::shared_ptr<BulletManager> bulletManager);

	void ProcessInput(const sf::Event & event) override;
	void Update(const sf::Time & elapsedTime) override;
	void Render(sf::RenderTarget & renderTarget) override;

	const sf::Vector2f& GetPosition() const { return _pos; }
	//sf::Sprite& GetSprite() { return _sprite; }
	void SetPosition(const sf::Vector2f pos) { _pos = pos; }
	float GetDistFromOriginToWeaponTip() const;

private:
	bool LoadTexture(const std::string & characterTexturePath);
		 
	void ProcessKeyboard();
	void ProcessMouse(const sf::Event & event);
		 
	void Move(const sf::Time & elapsedTime);
	void Rotate();

	std::weak_ptr<BulletManager> _bulletManager;

	sf::Vector2f	_pos;
	sf::Vector2f	_speed;
	sf::Vector2f	_unitSpeedVector;
	sf::Vector2f	_currentCursorPosition;
	//sf::Texture		_texture;
	//sf::Sprite		_sprite;
	float			_baseSpeed = 400.0f;
};