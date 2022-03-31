#pragma once

#include "GameObject.h"

class Enemy : public GameObject
{
public:
	void Init(const std::filesystem::path & resourcesDirectory);

	void ProcessInput(const sf::Event & event);
	void Update(const sf::Time & elapsedTime);
	void Render(sf::RenderTarget & renderTarget);
	void MoveTo(const sf::Vector2f & dest);

	const sf::RectangleShape& GetBoundingBox() const { return _boundingBox; }
	const sf::Vector2f& GetPosition() const { return _pos; }
	//sf::Sprite& GetSprite() { return _sprite; }
	bool IsDead() const { return _isDead; }

	void SetPosition(const sf::Vector2f pos) { _pos = pos; }
	void SetRemoveCondition(bool shouldRemove) { _isDead = shouldRemove; }

private:
	void InitBoundingBox();
	bool LoadTexture(const std::string & alienTexturePath);
	void Move(const sf::Time & elapsedTime);
	void Rotate();

	std::optional<sf::Vector2f>		_targetPos;
	sf::RectangleShape				_boundingBox;
	//sf::Texture						_texture;
	//sf::Sprite						_sprite;
	sf::Vector2f					_unitSpeedVector;
	sf::Vector2f					_pos;
	float							_baseSpeed = 300.0f;
	bool							_isDead = false;
};