#pragma once

class Character
{
public:
	void Init(const std::filesystem::path & resourcesDirectory);

	void ProcessInput(const sf::Event & event);
	void Update(sf::Time elapsedTime);
	void Render(sf::RenderTarget & renderTarget);

private:
	sf::Sprite		_sprite;
	sf::Texture		_texture;
	sf::Vector2f	_pos;
	sf::Vector2f	_speed;
};