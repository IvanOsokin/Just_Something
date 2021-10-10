#include "Character.h"

void Character::Init(const std::filesystem::path & resourcesDirectory, std::shared_ptr<sf::RenderWindow> window)
{
	Assert(window);

	//Downloading the character's texture and asigning it to the sprite
	const std::string characterTextureName = "character-1.png";
	auto characterTexturePath = resourcesDirectory / characterTextureName;

	std::string characterTexturePathStr = characterTexturePath.generic_string();

	if (window)
	{
		if (_texture.loadFromFile(characterTexturePathStr))
		{
			_sprite.setTexture(_texture);
			LOG_INFO() << "The character's texture was downloaded.";

			//Putting the character (initial state) in the middle of the scene
			sf::Vector2u textureSize = _texture.getSize();
			sf::Vector2u windowSize = window->getSize();

			_pos.x = (windowSize.x - textureSize.x) / 2.0f;
			_pos.y = (windowSize.y - textureSize.y) / 2.0f;
		}
		else
		{
			LOG_ERROR() << "Failed to download the character's texture.";
		}

		_sprite.setPosition(_pos);
	}
	else
	{
		LOG_ERROR() << "The window was lost.";
	}
}

void Character::ProcessInput(const sf::Event & event)
{
	static bool isWPressed = false;
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)		isWPressed = true;
	else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::W) isWPressed = false;

	static bool isSPressed = false;
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)		isSPressed = true;
	else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S) isSPressed = false;

	static bool isAPressed = false;
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)		isAPressed = true;
	else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A) isAPressed = false;

	static bool isDPressed = false;
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)		isDPressed = true;
	else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::D) isDPressed = false;

	if (isDPressed && isWPressed)		{ ++_pos.x; --_pos.y; }
	else if (isAPressed && isWPressed)	{ --_pos.x; --_pos.y; }
	else if (isDPressed && isSPressed)	{ ++_pos.x; ++_pos.y; }
	else if (isAPressed && isSPressed)	{ --_pos.x; ++_pos.y; }
	else if (isWPressed)				{ --_pos.y; }
	else if (isSPressed)				{ ++_pos.y; }
	else if (isAPressed)				{ --_pos.x; }
	else if (isDPressed)				{ ++_pos.x; }
}

void Character::Update(sf::Time /*elapsedTime*/)
{
	_sprite.setPosition(_pos);
}

void Character::Render(sf::RenderTarget & renderTarget)
{
	renderTarget.draw(_sprite);
}
