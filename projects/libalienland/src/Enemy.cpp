#include "Enemy.h"
#include "Utils.h"
#include "SfmlUtils.h"

void Enemy::Init(const std::filesystem::path & resourcesDirectory, sf::FloatRect localBounds)
{
	_localBounds = localBounds;

	const std::string enemyTextureName = "enemy-1.png";
	auto enemyTexturePath = resourcesDirectory / enemyTextureName;
	std::string enemyTexturePathStr = enemyTexturePath.generic_string();

	if (!LoadTexture(enemyTexturePathStr))
	{
		return;
	}
}

void Enemy::ProcessInput(const sf::Event & event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
	{
		auto target = Utils::VectorCast<float>(event.mouseButton.x, event.mouseButton.y);
		MoveTo(target);
	}
}

void Enemy::Update(float elapsedTime)
{
	Move(elapsedTime);
	Rotate();
}

void Enemy::ProcessCollision()
{

}

void Enemy::MoveTo(const sf::Vector2f & dest)
{
	_targetPos = dest;
}

bool Enemy::LoadTexture(const std::string & enemyTexturePath)
{
	if (!_texture.loadFromFile(enemyTexturePath))
	{
		LOG_ERROR() << "Failed to load the enemy's texture.";
		return false;
	}

	LOG_INFO() << "Successful loading the enemy texture.";
	return true;
}

void Enemy::Move(float elapsedTime)
{
	if (!_targetPos)
	{
		return;
	}

	sf::Vector2f speedVector = *_targetPos - Transform().GetPosition();
	float speedVectorLength = Utils::VectorLength(speedVector);

	const float eps = 0.5f;			// Необходим eps, чтобы враг не дергался, когда догоняет игрока
	if (speedVectorLength >= eps)
	{
		_unitSpeedVector = speedVector / speedVectorLength;
		Transform().Move(sf::Vector2f(_baseSpeed * _unitSpeedVector) * elapsedTime);
	}
	else
	{
		_targetPos.reset();
	}

	// Раскомментить, когда начальные позиции врага и персонажа будут отличаться
	//_unitSpeedVector = speedVector / speedVectorLength;
	//_sprite.move(sf::Vector2f(_baseSpeed * _unitSpeedVector) * elapsedTime.asSeconds());
	//_pos = _sprite.getPosition();

	//const float eps = 0.5f;			// Необходим eps, чтобы враг не дергался, когда догоняет игрока
	//if (speedVectorLength < eps)
	//{
	//	_targetPos.reset();
	//}
}

void Enemy::Rotate()
{
	const float angle = std::acosf(_unitSpeedVector.x);

	if (_unitSpeedVector.y < 0)
	{
		Transform().SetRotation(Utils::RadiansToDegrees(2 * Utils::pi - angle));
		return;
	}

	Transform().SetRotation(Utils::RadiansToDegrees(angle));
}
