#pragma once

class Enemy
{
public:
	void			Init(const std::filesystem::path& resourcesDirectory, std::shared_ptr<sf::RenderWindow> window);

	void			ProcessInput(const sf::Event & event);
	void			Update(const sf::Time & elapsedTime, const sf::Sprite & sprite);
	void			Render(sf::RenderTarget & renderTarget);

	sf::Sprite&		GetSprite() { return _sprite; }

private:
	bool			LoadTexture(const std::string & alienTexturePath);
	void			Position(const sf::Time & elapsedTime, const sf::Sprite& sprite);
	void			Rotate();

	sf::Sprite					_sprite;
	sf::Texture					_texture;
	sf::Vector2f				_pos;
	sf::Vector2f				_speed;
	sf::Vector2f				_unitSpeedVector;
	float						_baseSpeed = 300.0f;
};