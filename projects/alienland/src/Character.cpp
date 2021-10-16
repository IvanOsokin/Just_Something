#include "Character.h"

void Character::Init(const std::filesystem::path & resourcesDirectory, std::shared_ptr<sf::RenderWindow> window)
{
	Assert(window);

	//Loading the character's texture and asigning it to the sprite
	const std::string characterTextureName = "character-1.png";
	auto characterTexturePath = resourcesDirectory / characterTextureName;

	std::string characterTexturePathStr = characterTexturePath.generic_string();

	LoadTexture(characterTexturePathStr);
}

void Character::ProcessInput(const sf::Event& /*event*/)
{
	_unitSpeedVector.x = 0;
	_unitSpeedVector.y = 0;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { _unitSpeedVector.y -= 1; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { _unitSpeedVector.y += 1; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { _unitSpeedVector.x -= 1; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { _unitSpeedVector.x += 1; }

	if (_unitSpeedVector.x != 0 && _unitSpeedVector.y != 0)				// Ётот блок изначально был добавлен в метод Update.
	{																	// ѕри нажатии двух клавиш происходила задержка.
		const float decreasingCoef = static_cast<float>(pow(2, 0.5));	// Ћоги показывали, что идет посто€нное уменьшение _unitSpeedVector
		_unitSpeedVector /= decreasingCoef;								// “.е. ProcessInput не вызываетс€ и _unitSpeedVector не обнул€етс€ 
	}																	// и не происходит переопределение базового вектора
}

void Character::Update(sf::Time elapsedTime)
{
	_sprite.move(sf::Vector2f(_baseSpeed * _unitSpeedVector) * elapsedTime.asSeconds());
}

void Character::Render(sf::RenderTarget& renderTarget)
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
	LOG_INFO() << "The character's texture was loaded.";
	return true;
}