#include "Character.h"

#include "BulletManager.h"

void Character::Init(const std::filesystem::path & resourcesDirectory, std::shared_ptr<BulletManager> bulletManager)
{
	_bulletManager = bulletManager;

	//Loading the character's texture and asigning it to the sprite
	const std::string characterTextureName = "character-1.png";
	auto characterTexturePath = resourcesDirectory / characterTextureName;

	std::string characterTexturePathStr = characterTexturePath.generic_string();

	LoadTexture(characterTexturePathStr);
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
		auto targetPos = sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

		auto vectorToWeaponTip = targetPos - _sprite.getPosition();
		float distToWeaponTip = std::powf((std::powf(vectorToWeaponTip.x, 2.0f) + std::powf(vectorToWeaponTip.y, 2.0f)), 0.5f);
		if (distToWeaponTip < 122.33f)	// 122.33f - distance between _sprite.getOrigin() and the weapon tip.
		{								// This distance will change depending on weapon type
			return;						// or will be the same for different weapon types
		}

		_bulletManager->AddBullet(_sprite.getPosition(), _sprite.getRotation() + 15, targetPos);	// 15 deg - angle between the initial
	}																								// sprite position and the weapon tip
}

void Character::Move(const sf::Time & elapsedTime)
{
	_sprite.move(sf::Vector2f(_baseSpeed * _unitSpeedVector) * elapsedTime.asSeconds());
	_pos = _sprite.getPosition();
}

void Character::Rotate()
{
	sf::Vector2f viewDirectionVector = _currentCursorPosition - _pos;

	float viewDirectionVectorLength = std::powf((std::powf(viewDirectionVector.x, 2.0f) + std::powf(viewDirectionVector.y, 2.0f)), 0.5f);

	const float eps = 1.0f;
	if (viewDirectionVectorLength <= eps)
	{
		return;
	}

	sf::Vector2f unitViewDirectionVector;
	unitViewDirectionVector = viewDirectionVector / viewDirectionVectorLength;

	const float pi = 3.141593f;
	static const float s_fromRadToDeg = 180.0f / pi;

	const float angle = std::acosf(unitViewDirectionVector.x);

	if (unitViewDirectionVector.y < 0)
	{
		_sprite.setRotation((2 * pi - angle) * s_fromRadToDeg);
		return;
	}

	_sprite.setRotation(angle * s_fromRadToDeg);
}