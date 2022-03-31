#pragma once

#include "SFML/Graphics.hpp"

class GameObject
{
public:
	virtual ~GameObject() {};

	virtual void ProcessInput(const sf::Event & /*event*/) {};
	virtual void Update(const sf::Time & /*elapsedTime*/) {};
	virtual void Render(sf::RenderTarget & /*renderTarget*/) {};

	enum class GameObjectID
	{
		character,
		enemy,
		bullet
	};

	GameObjectID GetGameObjectID() const { return _gameObjectId; }

protected:
	sf::Texture& GetTexture() { return _texture; }
	sf::Sprite& GetSprite() { return _sprite; }	// sf::Sprite & GetSprite() const { return _sprite; }. Why so?
													// Отброшены квалификаторы в ссылке, привязывающей тип "sf::Sprite &" к инициализатору типа "const sf::Sprite"

private:
	sf::Texture  _texture;
	sf::Sprite	 _sprite;
	GameObjectID _gameObjectId;
};