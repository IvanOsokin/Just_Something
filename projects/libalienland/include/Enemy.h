#pragma once
#include "GameObject.h"

class GameScene;

class Enemy : public GameObject
{
public:
	void Init(const std::filesystem::path & resourcesDirectory, std::shared_ptr<GameScene> gameScene);

	void ProcessInput(const sf::Event & event) override;
	void Update(const sf::Time & elapsedTime) override;
	void Render(sf::RenderTarget & renderTarget) override;
	void ProcessCollision() override;

	void MoveTo(const sf::Vector2f & dest);
	sf::FloatRect GetBoundingBox() const { return _boundingBox.getGlobalBounds(); }
	const sf::Vector2f& GetPosition() const { return _pos; }
	void SetPosition(const sf::Vector2f pos) { _pos = pos; }

private:
	void InitBoundingBox();
	bool LoadTexture(const std::string & alienTexturePath);
	void Move(const sf::Time & elapsedTime);
	void Rotate();

	std::weak_ptr<GameScene>		_gameScene;

	std::optional<sf::Vector2f>		_targetPos;
	sf::RectangleShape				_boundingBox;
	sf::Sprite						_sprite;
	sf::Vector2f					_unitSpeedVector;
	sf::Vector2f					_pos;
	float							_baseSpeed = 300.0f;
};