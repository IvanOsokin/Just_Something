#pragma once

#include "SFML/Graphics.hpp"

class GameObject
{
public:
	virtual ~GameObject() {};

	virtual void ProcessInput(const sf::Event& /*event*/) {};
	virtual void Update(const sf::Time& /*elapsedTime*/) {};
	virtual void Render(sf::RenderTarget& /*renderTarget*/) {};
	virtual void ProcessCollision() {};

	enum class GameObjectType
	{
		character,
		enemy,
		bullet
	};

	GameObjectType GetGameObjectType() { return _gameObjectId; }
	void SetGameObjectId(GameObjectType gameObjectId) { _gameObjectId = gameObjectId; }
	bool ShouldRemove() const { return _shouldRemove; }
	void SetShouldRemoveState(bool shouldRemove) { _shouldRemove = shouldRemove; }

protected:
	sf::Texture& GetTexture() { return _texture; }
	sf::Sprite& GetSprite() { return _sprite; }
	void SetSprite(sf::Sprite&& sprite) { _sprite = sprite; }

private:
	sf::Texture		_texture;
	sf::Sprite		_sprite;
	GameObjectType	_gameObjectId;
	bool			_shouldRemove = false;
};