#include "Bullet.h"
#include "Enemy.h"
#include "GameScene.h"
#include "SfmlUtils.h"
#include "Utils.h"

void Bullet::Init(std::shared_ptr<GameScene> gameScene, float baseSpeed, std::optional<sf::Sprite> sprite, const sf::Vector2f & initPos, const sf::Vector2f & targetPos)
{
	_gameScene = gameScene;
	_baseSpeed = baseSpeed;
	SetGameObjectId(GameObject::GameObjectType::bullet);
	
	// Set initial position of the bullet on the tip of the weapon
	sprite->setOrigin(0.0f, sprite->getTexture()->getSize().y / 2.0f);
	sprite->setPosition(initPos);

	// Calculate the unit speed vector
	sf::Vector2f speedVector = targetPos - initPos;
	float speedVectorLength = Utils::VectorLength(speedVector);
	_unitSpeedVector = speedVector / speedVectorLength;

	// Rotate the bullet sprite
	const float angle = std::acosf(_unitSpeedVector.x);

	if (_unitSpeedVector.y < 0)
		sprite->setRotation(Utils::RadiansToDegrees(2 * Utils::pi - angle));
	else
		sprite->setRotation(Utils::RadiansToDegrees(angle));

	SetSprite(std::move(sprite.value()));
}

void Bullet::Update(const sf::Time & elapsedTime)
{
	sf::Vector2f offset = (_unitSpeedVector * _baseSpeed) * elapsedTime.asSeconds();
	GetSprite().move(offset);
}

void Bullet::Render(sf::RenderTarget & renderTarget)
{
	renderTarget.draw(GetSprite());
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
	const sf::FloatRect entityBound = GetSprite().getGlobalBounds();
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
		if (gameObject->GetGameObjectType() != GameObject::GameObjectType::enemy)
		{
			continue;
		}
		auto enemy = static_cast<Enemy*>(gameObject.get());
		const sf::FloatRect enemyBound = enemy->GetBoundingBox();
		const sf::FloatRect bulletBound = this->GetSprite().getGlobalBounds();
		if (!enemyBound.intersects(bulletBound))
		{
			continue;
		}
		this->SetShouldRemoveState(true);
		gameObject->SetShouldRemoveState(true);
		gameScene->SetShouldremoveGameObjectsState(true);
	}
}