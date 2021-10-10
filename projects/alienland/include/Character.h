#pragma once

struct Direction
{
	bool up		= false;
	bool down	= false;
	bool left	= false;
	bool right	= false;
};

class Character
{
public:
	void Init(const std::filesystem::path & resourcesDirectory, std::shared_ptr<sf::RenderWindow> window);

	void ProcessInput(const sf::Event & event);
	void Update(sf::Time elapsedTime);
	void Render(sf::RenderTarget & renderTarget);

private:
	sf::Vector2f GetStartPositon(std::shared_ptr<sf::RenderWindow> window);
	bool LoadTexture(std::shared_ptr<sf::RenderWindow> window, const std::string & characterTexturePath);

	sf::Sprite		_sprite;
	sf::Texture		_texture;
	sf::Vector2f	_pos;
	sf::Vector2f	_speed;

	Direction		_direction;
};