#include "Bullet.h"

Bullet::Bullet(const float & baseSpeed, const sf::Sprite & sprite)
	: _sprite(sprite)
	, _baseSpeed(baseSpeed)
{}

Bullet::~Bullet() = default;

Bullet& Bullet::operator= (const Bullet & bullet)
{
	_sprite = bullet._sprite;
	_bulletVertexes = bullet._bulletVertexes;
	_unitSpeedVector = bullet._unitSpeedVector;
	_baseSpeed = bullet._baseSpeed;

	return *this;
}

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
	}
	else
	{
		_sprite.setRotation(angle * s_fromRadToDeg);
	}

	// Initializing points for checking on the bullet sprite
	sf::Vector2f bulletBottom = _sprite.getOrigin();

	static const float s_fromDegToRad = pi / 180.0f;

	sf::Vector2f bulletTip;
	float bulletLength = static_cast<float>(_sprite.getTexture()->getSize().x);
	bulletTip.x = bulletLength * std::cosf(angle * s_fromDegToRad);
	bulletTip.y = bulletLength * std::sinf(angle * s_fromDegToRad);

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