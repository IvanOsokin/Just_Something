#pragma once

class Enemy
{
public:
	void				Init(const std::filesystem::path & resourcesDirectory, std::shared_ptr<sf::RenderWindow> window);

	void				ProcessInput();
	void				Update(const sf::Time & elapsedTime);
	void				Render(sf::RenderTarget & renderTarget);
	void				MoveTo(const sf::Vector2f & dest);

	const sf::Vector2f& GetPosition() const { return _pos; }
	void				SetPosition(const sf::Vector2f pos) { _pos = pos; }
	sf::Sprite&			GetSprite() { return _sprite; }

private:
	bool				LoadTexture(const std::string & alienTexturePath);
	void				Move(const sf::Time & elapsedTime);
	void				Rotate();

	sf::Sprite					_sprite;
	sf::Texture					_texture;
	sf::Vector2f				_pos;
	sf::Vector2f				_dest;
	sf::Vector2f				_speed;
	sf::Vector2f				_unitSpeedVector;
	float						_baseSpeed = 300.0f;
};