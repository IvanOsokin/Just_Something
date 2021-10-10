#include "Character.h"

void Character::Init(const std::filesystem::path & resourcesDirectory, std::shared_ptr<sf::RenderWindow> window)
{
	Assert(window);

	//Downloading the character's texture and asigning it to the sprite
	const std::string characterTextureName = "character-1.png";
	auto characterTexturePath = resourcesDirectory / characterTextureName;

	std::string characterTexturePathStr = characterTexturePath.generic_string();

	LoadTexture(window, characterTexturePathStr);

	_sprite.setPosition(GetStartPositon(window));
}

void Character::ProcessInput(const sf::Event & /*event*/)
{
	_direction.up    = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	_direction.down  = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	_direction.left  = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	_direction.right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
}

void Character::Update(sf::Time /*elapsedTime*/)
{
	if (_direction.up)		{ _speed.y = -1; }
	if (_direction.down)	{ _speed.y =  1; }
	if (_direction.left)	{ _speed.x = -1; }
	if (_direction.right)	{ _speed.x =  1; }

	_sprite.move(_speed);

	_speed.x = 0;
	_speed.y = 0;
}

void Character::Render(sf::RenderTarget & renderTarget)
{
	renderTarget.draw(_sprite);
}

sf::Vector2f Character::GetStartPositon(std::shared_ptr<sf::RenderWindow> window)
{
	if (!window)
	{
		LOG_ERROR() << "The window was lost.";
		return { 0.0f, 0.0f };
	}

    auto windowSize = window->getSize();
	auto textureSize = _texture.getSize();

	sf::Vector2f screenPosition;
	screenPosition.x = (windowSize.x - textureSize.x) / 2.0f;
	screenPosition.y = (windowSize.y - textureSize.y) / 2.0f;

	return screenPosition;
}

bool Character::LoadTexture(std::shared_ptr<sf::RenderWindow> window, const std::string & characterTexturePath)
{
	if (!_texture.loadFromFile(characterTexturePath))
	{
		LOG_INFO() << "The character's texture was downloaded.";
		return false;
	}

	_sprite.setTexture(_texture);
	LOG_ERROR() << "Failed to download the character's texture.";
	return true;
}