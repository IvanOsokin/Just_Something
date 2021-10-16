#include "Enemy.h"

void Enemy::Init(const std::filesystem::path & resourcesDirectory, std::shared_ptr<sf::RenderWindow> window)
{
	Assert(window);

	const std::string enemyTextureName = "enemy-1.png";
	auto enemyTexturePath = resourcesDirectory / enemyTextureName;

	std::string enemyTexturePathStr = enemyTexturePath.generic_string();

	LoadTexture(enemyTexturePathStr);
}

//void Enemy::ProcessInput(const sf::Event& /*event*/)
//{
//}

void Enemy::Update(sf::Time elapsedTime, const sf::Sprite & sprite)
{
	sf::Vector2f characterPosition(sprite.getPosition());
	_pos = _sprite.getPosition();

	sf::Vector2f speedVector = characterPosition - _pos;
	float speedVectorLength = static_cast<float>(pow((pow(speedVector.x, 2) + pow(speedVector.y, 2)), 0.5));

	const float eps = 2.0f;			// Необходим eps, чтобы враг не дергался, когда догоняет игрока
	if (speedVectorLength >= eps)
	{
		_unitSpeedVector = speedVector / speedVectorLength;
		_sprite.move(sf::Vector2f(_baseSpeed * _unitSpeedVector) * elapsedTime.asSeconds());
	}
}

void Enemy::Render(sf::RenderTarget & renderTarget)
{
	renderTarget.draw(_sprite);
}

bool Enemy::LoadTexture(const std::string& enemyTexturePath)
{
	if (!_texture.loadFromFile(enemyTexturePath))
	{
		LOG_ERROR() << "Failed to load the enemy's texture.";
		return false;
	}

	_sprite.setTexture(_texture);
	LOG_INFO() << "The enemy's texture was loaded.";
	return true;
}
