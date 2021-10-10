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

void Character::ProcessInput(const sf::Event & /*event*/)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))	_direction._up	  = true;
	else												_direction._up    = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))	_direction._down  = true;
	else												_direction._down  = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))	_direction._left  = true;
	else												_direction._left  = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))	_direction._right = true;
	else												_direction._right = false;
}

void Character::Update(sf::Time /*elapsedTime*/)
{
	if (_direction._right && _direction._up)        { ++_pos.x; --_pos.y; }
	else if (_direction._left && _direction._up)    { --_pos.x; --_pos.y; }
	else if (_direction._right && _direction._down) { ++_pos.x; ++_pos.y; }
	else if (_direction._left && _direction._down)  { --_pos.x; ++_pos.y; }
	else if (_direction._up)						{ --_pos.y; }
	else if (_direction._down)						{ ++_pos.y; }
	else if (_direction._left)						{ --_pos.x; }
	else if (_direction._right)						{ ++_pos.x; }
	
	_sprite.setPosition(_pos);
}

void Character::Render(sf::RenderTarget & renderTarget)
{
	renderTarget.draw(_sprite);
}
