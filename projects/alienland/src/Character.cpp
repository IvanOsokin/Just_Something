#include "Character.h"

void Character::Init(const std::filesystem::path & resourcesDirectory, std::shared_ptr<sf::RenderWindow> window)
{
	Assert(window);

	//Downloading the character's texture and asigning it to the sprite
	const std::string characterTextureName = "character-1.png";
	auto characterTexturePath = resourcesDirectory / characterTextureName;

	std::string characterTexturePathStr = characterTexturePath.generic_string();

	LoadTexture(characterTexturePathStr);

	_sprite.setPosition(GetStartPositon(window, _texture));
}

void Character::ProcessInput(const sf::Event& /*event*/)
{
	_unitSpeedVector.x = 0;
	_unitSpeedVector.y = 0;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { _unitSpeedVector.y = -1; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { _unitSpeedVector.y =  1; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { _unitSpeedVector.x = -1; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { _unitSpeedVector.x =  1; }
}

void Character::Update(sf::Time elapsedTime)
{
	_sprite.move(sf::Vector2f(_baseSpeed * _unitSpeedVector.x, _baseSpeed * _unitSpeedVector.y) * elapsedTime.asSeconds());
}

void Character::Render(sf::RenderTarget & renderTarget)
{
	renderTarget.draw(_sprite);
}

sf::Vector2f Character::GetStartPositon(std::shared_ptr<sf::RenderWindow> window, const sf::Texture & texture)
{
	if (!window)
	{
		LOG_ERROR() << "The window was lost.";
		return { 0.0f, 0.0f };
	}

    auto windowSize = window->getSize();
	auto textureSize = texture.getSize();

	sf::Vector2f positionOnScreen;
	positionOnScreen.x = (windowSize.x - textureSize.x) / 2.0f;
	positionOnScreen.y = (windowSize.y - textureSize.y) / 2.0f;

	return positionOnScreen;
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