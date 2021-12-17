#include "Bullet.h"
#include "Utils.h"

void Bullet::Init(float baseSpeed, const sf::Sprite & sprite, const sf::Vector2f & initPos, const sf::Vector2f & targetPos)
{
	_sprite = sprite;
	_baseSpeed = baseSpeed;

	// Set initial position of the bullet on the tip of the weapon
	_sprite.setOrigin(0.0f, _sprite.getTexture()->getSize().y / 2.0f);
	_sprite.setPosition(initPos);

	// Calculate the unit speed vector
	sf::Vector2f speedVector = targetPos - initPos;
	float speedVectorLength = Utils::VectorLength(speedVector);
	_unitSpeedVector = speedVector / speedVectorLength;

	// Rotate the bullet sprite
	const float angle = std::acosf(_unitSpeedVector.x);

	if (_unitSpeedVector.y < 0)
		_sprite.setRotation(Utils::RadiansToDegrees(2 * pi - angle));
	else
		_sprite.setRotation(Utils::RadiansToDegrees(angle));

	// Initializing points for checking on the bullet sprite
	const float bulletLength = static_cast<float>(_sprite.getTexture()->getSize().x);

	sf::Vector2f bulletTip;

	if (_unitSpeedVector.y < 0)
		bulletTip = sf::Vector2( bulletLength * std::cosf(2 * pi - angle), bulletLength * std::sinf(2 * pi - angle) );
	else
		bulletTip = sf::Vector2(bulletLength * std::cosf(angle), bulletLength * std::sinf(angle));

	_bulletVertexes._bottom = _sprite.getPosition();
	_bulletVertexes._tip = _bulletVertexes._bottom + bulletTip;
}

void Bullet::Update(const sf::Time & elapsedTime)
{
	sf::Vector2f offset = (_unitSpeedVector * _baseSpeed) * elapsedTime.asSeconds();

	_sprite.move(offset);
	_bulletVertexes._bottom += offset;
	_bulletVertexes._tip += offset;
}

void Bullet::Render(sf::RenderTarget & renderTarget)
{
	renderTarget.draw(_sprite);
}