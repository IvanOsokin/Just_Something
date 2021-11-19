#pragma once

// Добавить описание класса
class BulletManager;

class Character
{
public:
	void							Init(const std::filesystem::path & resourcesDirectory, std::shared_ptr<BulletManager> bulletManager);

	void							ProcessInput(const sf::RenderWindow & window, const sf::Event & event);
	void							Update(const sf::Time & elapsedTime);
	void							Render(sf::RenderTarget & renderTarget);

	sf::Sprite&						GetSprite() { return _sprite; }
	const sf::Vector2f&				GetPosition() const { return _pos; }
	void							SetPosition(const sf::Vector2f pos) { _pos = pos; }

private:
	bool							LoadTexture(const std::string & characterTexturePath);

	void							ProcessKeyboard();
	void							ProcessMouse(const sf::RenderWindow & window, const sf::Event & event);

	void							Move(const sf::Time & elapsedTime);
	void							Rotate();

	sf::Sprite						_sprite;
	sf::Texture						_texture;
	sf::Vector2f					_pos;
	sf::Vector2f					_speed;
	sf::Vector2f					_unitSpeedVector;
	sf::Vector2f					_currentCursorPosition;
	std::shared_ptr<BulletManager>	_bulletManager;
	float							_baseSpeed = 400.0f;
};