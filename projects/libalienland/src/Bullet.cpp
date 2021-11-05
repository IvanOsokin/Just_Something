#include "Bullet.h"

Bullet::Bullet(const float & baseSpeed, const sf::Sprite & sprite, const sf::VertexArray & bulletBoundingBoxes)
	: _sprite(sprite)
	, _baseSpeed(baseSpeed)
	, _boundingBoxes(bulletBoundingBoxes)
{}

Bullet::~Bullet() = default;

void Bullet::Init(const sf::Vector2f & initPos, const sf::Vector2f & targetPos)
{
	// Set initial position of the bullet on the tip of the weapon
	_sprite.setOrigin(0.0f, _sprite.getTexture()->getSize().y / 2.0f);
	_sprite.setPosition(initPos);

	// Calculate the unit speed vector
	sf::Vector2f speedVector = targetPos - initPos;
	float speedVectorLength = std::powf((std::powf(speedVector.x, 2.0f) + std::powf(speedVector.y, 2.0f)), 0.5f);
	_unitSpeedVector = speedVector / speedVectorLength;

	// Rotate the bullet sprite
	const float pi = 3.141593f;
	static const float s_fromRadToDeg = 180.0f / pi;

	const float angle = std::acosf(_unitSpeedVector.x);

	if (_unitSpeedVector.y < 0)
	{
		_sprite.setRotation((2 * pi - angle) * s_fromRadToDeg);
		return;
	}

	_sprite.setRotation(angle * s_fromRadToDeg);
}

void Bullet::Update(const sf::Time & elapsedTime)
{
	_sprite.move(sf::Vector2f((_unitSpeedVector * _baseSpeed) * elapsedTime.asSeconds()));
}

void Bullet::Render(sf::RenderTarget & renderTarget)
{
	renderTarget.draw(_sprite);
}