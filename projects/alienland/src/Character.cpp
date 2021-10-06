#include "Character.h"

void Character::Init(const std::filesystem::path & resourcesDirectory)
{
	const std::string characterTextureName = "character-1.png";
	auto characterTexturePath = resourcesDirectory / characterTextureName;

	std::string characterTexturePathStr = characterTexturePath.generic_string();

	std::replace(characterTexturePathStr.begin(), characterTexturePathStr.end(), '/', '\\');

	if (_texture.loadFromFile(characterTexturePathStr))
	{
		_sprite.setTexture(_texture);
		LOG_INFO("The character's texture was downloaded");
	}
	else
	{
		sf::err() << "Could not find the texture." << std::endl;
		LOG_INFO("Failed to download the character's texture");
	}
}

void Character::ProcessInput(const sf::Event& event)
{
}

void Character::Update(sf::Time elapsedTime)
{
}

void Character::Render(sf::RenderTarget & renderTarget)
{
	renderTarget.draw(_sprite);
}
