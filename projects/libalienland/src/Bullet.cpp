#include "Bullet.h"
#include "Enemy.h"
#include "GameScene.h"
#include "SfmlUtils.h"
#include "Utils.h"

void Bullet::Init(std::shared_ptr<GameScene> gameScene, float baseSpeed, std::optional<sf::Sprite> sprite, const sf::Vector2f & initPos, const sf::Vector2f & targetPos)
{
	_gameScene = gameScene;
	_baseSpeed = baseSpeed;
	if (!sprite)
	{
		LOG_ERROR() << "Could not load a sprite of the bullet";
		return;
	}
	_sprite = *sprite;
	
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
		_sprite.setRotation(Utils::RadiansToDegrees(2 * Utils::pi - angle));
	else
		_sprite.setRotation(Utils::RadiansToDegrees(angle));
}

void Bullet::Update(const sf::Time & elapsedTime)
{
	sf::Vector2f offset = (_unitSpeedVector * _baseSpeed) * elapsedTime.asSeconds();
	_sprite.move(offset);
}

void Bullet::ProcessCollision()
{
	SceneBorderCollision();
	if (ShouldRemove())
	{
		return;
	}
	EnemyCollision();
}

void Bullet::SceneBorderCollision()
{
	auto gameScene = _gameScene.lock();
	const sf::IntRect sceneBorder = gameScene->GetSceneBorder();
	const sf::FloatRect entityBound = _sprite.getGlobalBounds();
	if (Utils::RectCast<float>(sceneBorder).intersects(entityBound))
	{
		return;
	}
	this->SetShouldRemoveState(true);
	gameScene->SetShouldremoveGameObjectsState(true);
}

void Bullet::EnemyCollision()
{
	auto gameScene = _gameScene.lock();
	auto gameObjects = gameScene->GetGameObjects();
	for (auto gameObject : gameObjects)
	{
		auto enemy = std::dynamic_pointer_cast<Enemy>(gameObject);
		if (!enemy)
		{
			continue;
		}
		const sf::FloatRect enemyBound = enemy->GetBoundingBox();
		const sf::FloatRect bulletBound = this->_sprite.getGlobalBounds();
		if (!enemyBound.intersects(bulletBound))
		{
			continue;
		}
		this->SetShouldRemoveState(true);
		gameObject->SetShouldRemoveState(true);
		gameScene->SetShouldremoveGameObjectsState(true);
	}
}