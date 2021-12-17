#include "Character.h"

#include "BulletManager.h"
#include "Utils.h"

void Character::Init(const std::filesystem::path & resourcesDirectory, std::shared_ptr<BulletManager> bulletManager)
{
	_bulletManager = bulletManager;

	//Loading the character's texture and asigning it to the sprite
	const std::string characterTextureName = "character-1.png";
	auto characterTexturePath = resourcesDirectory / characterTextureName;

	std::string characterTexturePathStr = characterTexturePath.generic_string();

	if (!LoadTexture(characterTexturePathStr))
	{
		return;
	}

	_sprite.setOrigin(108.0f, 119.0f);
}

void Character::ProcessInput(const sf::Event & event)
{
	ProcessKeyboard();
	ProcessMouse(event);
}

void Character::Update(const sf::Time & elapsedTime)
{
	Move(elapsedTime);
	Rotate();

}

void Character::Render(sf::RenderTarget & renderTarget)
{
	renderTarget.draw(_sprite);
}

float Character::GetDistFromOriginToWeaponTip() const
{
	return _bulletManager.lock()->GetCurrentDistFormOriginToWeaponTip(/*Weapon ID*/);
}

bool Character::LoadTexture(const std::string & characterTexturePath)
{
	if (!_texture.loadFromFile(characterTexturePath))
	{
		LOG_ERROR() << "Failed to load the character's texture.";
		return false;
	}

	_sprite.setTexture(_texture);
	LOG_INFO() << "Successful loading the character texture.";
	return true;
}

void Character::ProcessKeyboard()
{
	_unitSpeedVector.x = 0;
	_unitSpeedVector.y = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { _unitSpeedVector.y -= 1; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { _unitSpeedVector.y += 1; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { _unitSpeedVector.x -= 1; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { _unitSpeedVector.x += 1; }

	if (_unitSpeedVector.x != 0 && _unitSpeedVector.y != 0)
	{
		const float decreasingCoef = static_cast<float>(pow(2, 0.5));
		_unitSpeedVector /= decreasingCoef;
	}
}

void Character::ProcessMouse(const sf::Event & event)
{
	if (event.type == sf::Event::EventType::MouseMoved)
	{
		_currentCursorPosition = sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
	}
	
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		const auto targetPos = sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

		const auto viewDirectionVector = targetPos - _sprite.getPosition();
		const float viewDirectionVectorLength = std::powf((std::powf(viewDirectionVector.x, 2.0f) + std::powf(viewDirectionVector.y, 2.0f)), 0.5f);

		const float distFromOriginToWeaponTip = GetDistFromOriginToWeaponTip();

		if (viewDirectionVectorLength < distFromOriginToWeaponTip)
		{
			return;
		}

		_bulletManager.lock()->AddBullet(_sprite.getPosition(), _sprite.getRotation(), targetPos);
	}
}

void Character::Move(const sf::Time & elapsedTime)
{
	_sprite.move(sf::Vector2f(_baseSpeed * _unitSpeedVector) * elapsedTime.asSeconds());
	_pos = _sprite.getPosition();
}

void Character::Rotate()
{
	sf::Vector2f viewDirectionVector = _currentCursorPosition - _pos;

	float viewDirectionVectorLength = Utils::VectorLength(viewDirectionVector);

	const float eps = 1.0f;
	if (viewDirectionVectorLength <= eps)
	{
		return;
	}

	sf::Vector2f unitViewDirectionVector;
	unitViewDirectionVector = viewDirectionVector / viewDirectionVectorLength;

	const float angle = std::acosf(unitViewDirectionVector.x);
	
	if (unitViewDirectionVector.y < 0)
	{
		_sprite.setRotation(Utils::RadiansToDegrees(2 * pi - angle));
		return;
	}

	_sprite.setRotation(Utils::RadiansToDegrees(angle));
}