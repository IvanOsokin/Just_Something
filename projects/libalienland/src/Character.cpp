#include "Character.h"

#include "BulletManager.h"
#include "GameScene.h"
#include "Utils.h"
#include "SfmlUtils.h"

void Character::Init(const std::filesystem::path & resourcesDirectory, std::shared_ptr<GameScene> gameScene, std::shared_ptr<BulletManager> bulletManager)
{
	_gameScene = gameScene;
	_bulletManager = bulletManager;

	const std::string characterTextureName = "character-1.png";
	auto characterTexturePath = resourcesDirectory / characterTextureName;
	std::string characterTexturePathStr = characterTexturePath.generic_string();

	if (!LoadTexture(characterTexturePathStr))
	{
		return;
	}
}

void Character::ProcessInput(const sf::Event & event)
{
	ProcessKeyboard();
	ProcessMouse(event);
}

void Character::Update(float elapsedTime)
{
	Move(elapsedTime);
	Rotate();

}

void Character::ProcessCollision()
{

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
		const float decreasingCoef = std::sqrtf(2.0f);
		_unitSpeedVector /= decreasingCoef;
	}
}

void Character::ProcessMouse(const sf::Event & event)
{
	if (event.type == sf::Event::EventType::MouseMoved)
	{
		_currentCursorPosition = Utils::VectorCast<float>(event.mouseMove.x, event.mouseMove.y);
	}
	
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		const auto targetPos = Utils::VectorCast<float>(event.mouseButton.x, event.mouseButton.y);
		const auto viewDirectionVector = targetPos - Transform().GetPosition();
		const float viewDirectionVectorLength = Utils::VectorLength(viewDirectionVector);
		const float distFromOriginToWeaponTip = GetDistFromOriginToWeaponTip();

		if (viewDirectionVectorLength < distFromOriginToWeaponTip)
		{
			return;
		}
		auto gameScene = _gameScene.lock();
		gameScene->AddBullet(gameScene, Transform().GetPosition(), Transform().GetRotation(), targetPos);
	}
}

void Character::Move(float elapsedTime)
{
	Transform().Move(sf::Vector2f(_baseSpeed * _unitSpeedVector) * elapsedTime);
}

void Character::Rotate()
{
	sf::Vector2f viewDirectionVector = _currentCursorPosition - Transform().GetPosition();

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
		Transform().SetRotation(Utils::RadiansToDegrees(2 * Utils::pi - angle));
		return;
	}

	Transform().SetRotation(Utils::RadiansToDegrees(angle));
}