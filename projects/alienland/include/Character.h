#pragma once

class Character
{
public:
	void				Init(const std::filesystem::path & resourcesDirectory);

	void				ProcessInput(const sf::Event & event);
	void				Update(const sf::Time & elapsedTime );
	void				Render(sf::RenderTarget & renderTarget);

	sf::Sprite&			GetSprite() { return _sprite; }
	const sf::Vector2f& GetPosition() const { return _pos; }
	void				SetPosition(const sf::Vector2f pos) { _pos = pos; }

private:
	bool				LoadTexture(const std::string & characterTexturePath);

	sf::Sprite			_sprite;
	sf::Texture			_texture;
	sf::Vector2f		_pos;
	sf::Vector2f		_speed;
	sf::Vector2f		_unitSpeedVector;
	float				_baseSpeed = 400.0f;
};