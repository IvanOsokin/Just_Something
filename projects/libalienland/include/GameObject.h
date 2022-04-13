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

	GameObjectType GetGameObjectType() { return _gameObjectType; }
	void SetGameObjectId(GameObjectType gameObjectId) { _gameObjectType = gameObjectId; }
	bool ShouldRemove() const { return _shouldRemove; }
	void SetShouldRemoveState(bool shouldRemove) { _shouldRemove = shouldRemove; }

protected:
	sf::Texture& GetTexture() { return _texture; }

private:
	sf::Texture		_texture;
	GameObjectType	_gameObjectType;
	bool			_shouldRemove = false;
};