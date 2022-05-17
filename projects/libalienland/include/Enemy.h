#pragma once
#include "GameObject.h"

class GameScene;

class Enemy : public GameObject
{
public:
	void Init(const std::filesystem::path & resourcesDirectory, sf::FloatRect localBounds);

	void ProcessInput(const sf::Event & event) override;
	void Update(float elapsedTime) override;
	void ProcessCollision() override;

	void MoveTo(const sf::Vector2f & dest);

	sf::FloatRect GetLocalBounds() const { return _localBounds; }
	const sf::Texture & GetTexture() const { return _texture; }

private:
	bool LoadTexture(const std::string & alienTexturePath);
	void Move(float elapsedTime);
	void Rotate();

	std::optional<sf::Vector2f>		_targetPos;
	sf::FloatRect					_localBounds;
	sf::Texture						_texture;
	sf::Vector2f					_unitSpeedVector;
	float							_baseSpeed = 300.0f;
};