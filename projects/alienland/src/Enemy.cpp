#include "Enemy.h"

void Enemy::Init(const std::filesystem::path & resourcesDirectory, std::shared_ptr<sf::RenderWindow> window)
{
	Assert(window);

	const std::string enemyTextureName = "enemy-1.png";
	auto enemyTexturePath = resourcesDirectory / enemyTextureName;

	std::string enemyTexturePathStr = enemyTexturePath.generic_string();

	LoadTexture(enemyTexturePathStr);
}

void Enemy::ProcessInput(const sf::Event& event)
{
	if (/*event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right ||*/
		event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
	{
		auto target = sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
		MoveTo(target);
		LOG_DEBUG() << "Enemy move to " << target.x << " " << target.y;
	}
}
//
// const sf::Vector2f Enemy::ProcessInput(std::shared_ptr<sf::RenderWindow> window)
// {
// 	if (!sf::Mouse::isButtonPressed(sf::Mouse::Right))
// 	{
// 		return _dest;
// 	}
//
// 	return(sf::Vector2f(sf::Mouse::getPosition(*window)));
// }

void Enemy::Update(const sf::Time & elapsedTime)
{
	Move(elapsedTime);
	Rotate();
}

void Enemy::Render(sf::RenderTarget & renderTarget)
{
	renderTarget.draw(_sprite);
}

void Enemy::MoveTo(const sf::Vector2f & dest)
{
	_targetPos = dest;
	// _dest = dest;
}

bool Enemy::LoadTexture(const std::string & enemyTexturePath)
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

void Enemy::Move(const sf::Time & elapsedTime)
{
	if (!_targetPos)
	{
		return;
	}

	sf::Vector2f speedVector = *_targetPos - _pos;
	float speedVectorLength = std::powf((std::powf(speedVector.x, 2.0f) + std::powf(speedVector.y, 2.0f)), 0.5f);

	_unitSpeedVector = speedVector / speedVectorLength;
	_sprite.move(sf::Vector2f(_baseSpeed * _unitSpeedVector) * elapsedTime.asSeconds());
	_pos = _sprite.getPosition();

	const float eps = 0.5f;			// ��������� eps, ����� ���� �� ��������, ����� �������� ������
	if (speedVectorLength < eps)
	{
		_targetPos.reset();
	}
}

void Enemy::Rotate()
{
	const float pi = 3.141593f;
	const float fromRadToDeg = 180.0f / pi;

	const float angle = std::acosf(_unitSpeedVector.x);

	if (_unitSpeedVector.y < 0)
	{
		_sprite.setRotation((2 * pi - angle) * fromRadToDeg);
		return;
	}

	_sprite.setRotation(angle * fromRadToDeg);
}
