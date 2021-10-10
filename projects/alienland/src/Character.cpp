#include "Character.h"

void Character::Init(const std::filesystem::path & resourcesDirectory, std::shared_ptr<sf::RenderWindow> window)
{
	Assert(window);

	//Downloading the character's texture and asigning it to the sprite
	const std::string characterTextureName = "character-1.png";
	auto characterTexturePath = resourcesDirectory / characterTextureName;

	std::string characterTexturePathStr = characterTexturePath.generic_string();

	if (_texture.loadFromFile(characterTexturePathStr))
	{
		_sprite.setTexture(_texture);
		LOG_INFO() << "The character's texture was downloaded";
	}
	else
	{
		LOG_ERROR() << "Failed to download the character's texture";
	}

	//Putting the character (initial state) in the middle of the scene
	sf::Vector2u textureSize = _texture.getSize();
	sf::Vector2u windowSize = window->getSize();

	_pos.x = (windowSize.x - textureSize.x) / 2.0f;
	_pos.y = (windowSize.y - textureSize.y) / 2.0f;

	_sprite.setPosition(_pos);
}

void Character::ProcessInput(const sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::W)	--_pos.y;
		if (event.key.code == sf::Keyboard::S)	++_pos.y;
		if (event.key.code == sf::Keyboard::D)	++_pos.x;
		if (event.key.code == sf::Keyboard::A)	--_pos.x;
	}
}

void Character::Update(sf::Time /*elapsedTime*/)
{
	_sprite.setPosition(_pos);
}

void Character::Render(sf::RenderTarget & renderTarget)
{
	renderTarget.draw(_sprite);
}
