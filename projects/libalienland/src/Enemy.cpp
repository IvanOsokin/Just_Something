#include "Enemy.h"

void Enemy::Init(const std::filesystem::path & resourcesDirectory, std::shared_ptr<sf::RenderWindow> window)
{
	Assert(window);

	const std::string enemyTextureName = "enemy-1.png";
	auto enemyTexturePath = resourcesDirectory / enemyTextureName;

	std::string enemyTexturePathStr = enemyTexturePath.generic_string();

	LoadTexture(enemyTexturePathStr);
}

void Enemy::ProcessInput(const sf::Event & event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
	{
		auto target = sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
		MoveTo(target);
	}
}

void Enemy::Update(const sf::Time & elapsedTime)
{
	Move(elapsedTime);
	Rotate();
}

void Enemy::Render(sf::RenderTarget & renderTarget)
{
	renderTarget.draw(_sprite);
	renderTarget.draw(_boundingBox);
}

void Enemy::MoveTo(const sf::Vector2f & dest)
{
	_targetPos = dest;
}

void Enemy::InitBoundingBox()
{
	_boundingBox.setOutlineColor(sf::Color::Yellow);
	_boundingBox.setFillColor(sf::Color::Transparent);
	_boundingBox.setOutlineThickness(2.0f);

	/////// Depending on the type of the enemy /////////
	_boundingBox.setSize(sf::Vector2f(84.0f, 32.0f));
	////////////////////////////////////////////////////
	_boundingBox.setOrigin(_boundingBox.getSize().x / 2.0f + 32, _boundingBox.getSize().y / 2.0f - 14);
	_boundingBox.setPosition(_sprite.getPosition());
	_boundingBox.setRotation(_sprite.getRotation());
}

bool Enemy::LoadTexture(const std::string & enemyTexturePath)
{
	if (!_texture.loadFromFile(enemyTexturePath))
	{
		LOG_ERROR() << "Failed to load the enemy's texture.";
		return false;
	}

	_sprite.setTexture(_texture);
	LOG_INFO() << "Successful loading the enemy texture.";
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

	const float eps = 0.5f;			// Необходим eps, чтобы враг не дергался, когда догоняет игрока
	if (speedVectorLength >= eps)
	{
		_unitSpeedVector = speedVector / speedVectorLength;
		_sprite.move(sf::Vector2f(_baseSpeed * _unitSpeedVector) * elapsedTime.asSeconds());
		_pos = _sprite.getPosition();
		_boundingBox.setPosition(_pos);
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
	const float pi = 3.141593f;
	static const float s_fromRadToDeg = 180.0f / pi;

	const float angle = std::acosf(_unitSpeedVector.x);

	if (_unitSpeedVector.y < 0)
	{
		_sprite.setRotation((2 * pi - angle) * s_fromRadToDeg);
		///// Template data /////
		_boundingBox.setRotation(_sprite.getRotation());
		/////////////////////////
		return;
	}

	_sprite.setRotation(angle * s_fromRadToDeg);
	///// Template data /////
	_boundingBox.setRotation(_sprite.getRotation());
	/////////////////////////
}
