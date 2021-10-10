#pragma once

struct Direction
{
	bool _up	= false;
	bool _down	= false;
	bool _left	= false;
	bool _right	= false;
};

class Character
{
public:
	void Init(const std::filesystem::path & resourcesDirectory, std::shared_ptr<sf::RenderWindow> window);

	void ProcessInput(const sf::Event & event);
	void Update(sf::Time elapsedTime);
	void Render(sf::RenderTarget & renderTarget);

private:
	sf::Sprite		_sprite;
	sf::Texture		_texture;
	sf::Vector2f	_pos;
	sf::Vector2f	_speed;

	Direction		_direction;
};