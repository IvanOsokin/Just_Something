#include "Bullet.h"
#include "Enemy.h"
#include "GameScene.h"
#include "SfmlUtils.h"
#include "Utils.h"

void Bullet::Init(std::shared_ptr<GameScene> gameScene, float baseSpeed, sf::FloatRect localBounds, const sf::Vector2f & initPos, const sf::Vector2f & targetPos)
{
	_gameScene = gameScene;
	_baseSpeed = baseSpeed;
	_localBounds = localBounds;

	// Set initial position of the bullet on the tip of the weapon
	Transform().SetOrigin(0.0f, _localBounds.top / 2.0f);
	Transform().SetPosition(initPos);

	// Calculate the unit speed vector
	sf::Vector2f speedVector = targetPos - initPos;
	float speedVectorLength = Utils::VectorLength(speedVector);
	_unitSpeedVector = speedVector / speedVectorLength;

	// Rotate the bullet sprite
	const float angle = std::acosf(_unitSpeedVector.x);

	if (_unitSpeedVector.y < 0)
		Transform().SetRotation(Utils::RadiansToDegrees(2 * Utils::pi - angle));
	else
		Transform().SetRotation(Utils::RadiansToDegrees(angle));
}

void Bullet::Update(const sf::Time & elapsedTime)
{
	sf::Vector2f offset = (_unitSpeedVector * _baseSpeed) * elapsedTime.asSeconds();
	Transform().Move(offset);
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
	const sf::FloatRect entityBound = Transform().GetTransform().transformRect(_localBounds);
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
		const sf::FloatRect enemyBound = enemy->Transform().GetTransform().transformRect(enemy->GetLocalBounds());
		const sf::FloatRect bulletBound = Transform().GetTransform().transformRect(_localBounds);
		if (!enemyBound.intersects(bulletBound))
		{
			continue;
		}
		this->SetShouldRemoveState(true);
		gameObject->SetShouldRemoveState(true);
		gameScene->SetShouldremoveGameObjectsState(true);
	}
}