#include "Character.h"

void Character::Init(const std::filesystem::path & resourcesDirectory, std::shared_ptr<sf::RenderWindow> window)
{
	Assert(window);

	//Downloading the character's texture and asigning it to the sprite
	const std::string characterTextureName = "character-1.png";
	auto characterTexturePath = resourcesDirectory / characterTextureName;

	std::string characterTexturePathStr = characterTexturePath.generic_string();

	SetStartPositon(window, characterTexturePathStr);

	_sprite.setPosition(_pos);

}

void Character::ProcessInput(const sf::Event & /*event*/)
{
	_direction.up    = (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ? true : false);
	_direction.down  = (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ? true : false);
	_direction.left  = (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ? true : false);
	_direction.right = (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ? true : false);
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

void Character::SetStartPositon(std::shared_ptr<sf::RenderWindow> window, std::string characterTexturePath)
{
	if (!window)
	{
		LOG_ERROR() << "The window was lost.";
		return;
	}

	if (DownloadTexture(window, characterTexturePath))
	{
		//Putting the character (initial state) in the middle of the scene
		sf::Vector2u textureSize = _texture.getSize();
		sf::Vector2u windowSize = window->getSize();

		_pos.x = (windowSize.x - textureSize.x) / 2.0f;
		_pos.y = (windowSize.y - textureSize.y) / 2.0f;
	}
}

bool Character::DownloadTexture(std::shared_ptr<sf::RenderWindow> window, std::string characterTexturePath)
{
	if (_texture.loadFromFile(characterTexturePath))
	{
		_sprite.setTexture(_texture);
		LOG_INFO() << "The character's texture was downloaded.";
		return true;
	}
	else
	{
		LOG_ERROR() << "Failed to download the character's texture.";
		return false;
	}
}
