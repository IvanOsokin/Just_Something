#pragma once

class Enemy
{
public:
	void						Init(const std::filesystem::path & resourcesDirectory, std::shared_ptr<sf::RenderWindow> window);
	void						InitBoundingBox();

	void						ProcessInput(const sf::Event & event);
	void						Update(const sf::Time & elapsedTime);
	void						Render(sf::RenderTarget & renderTarget);
	void						MoveTo(const sf::Vector2f & dest);

	const sf::RectangleShape&	GetBoundingBox() const { return _boundingBox; }
	const sf::Vector2f&			GetPosition() const { return _pos; }
	sf::Sprite&					GetSprite() { return _sprite; }
	bool						IsDead() const { return _isDead; }

	void						SetPosition(const sf::Vector2f pos) { _pos = pos; }
	void						SetRemoveCondition(bool shouldRemove) { _isDead = shouldRemove; }

private:
	bool				LoadTexture(const std::string & alienTexturePath);
	void				Move(const sf::Time & elapsedTime);
	void				Rotate();

	sf::Sprite					_sprite;
	sf::Texture					_texture;
	sf::RectangleShape			_boundingBox;

	sf::Vector2f				_pos;
	//sf::Vector2f				_speed;
	sf::Vector2f				_unitSpeedVector;
	bool						_isDead = false;

	float						_baseSpeed = 300.0f;

	std::optional<sf::Vector2f>	_targetPos;
};