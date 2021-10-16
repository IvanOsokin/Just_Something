#pragma once

class Character
{
public:
	void			Init(const std::filesystem::path & resourcesDirectory, std::shared_ptr<sf::RenderWindow> window);

	void			ProcessInput(const sf::Event & event);
	void			Update(sf::Time elapsedTime);
	void			Render(sf::RenderTarget & renderTarget);

	sf::Sprite&		GetSprite() { return _sprite; };
	sf::Sprite		GetSprite() const { return _sprite; };

private:
	bool			LoadTexture(const std::string & characterTexturePath);

	sf::Sprite		_sprite;
	sf::Texture		_texture;
	sf::Vector2f	_pos;
	sf::Vector2f	_speed;
	sf::Vector2f	_unitSpeedVector;
	float			_baseSpeed = 3000000.0f;
};