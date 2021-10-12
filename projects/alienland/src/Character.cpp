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

	//Initializing unit speed vector
	_unitSpeedVector.emplace_back(std::move(sf::Vector2f( 0.0f, -1.0f)));	// move up
	_unitSpeedVector.emplace_back(std::move(sf::Vector2f( 0.0f,  1.0f)));	// move down
	_unitSpeedVector.emplace_back(std::move(sf::Vector2f(-1.0f,  0.0f)));	// move to the left
	_unitSpeedVector.emplace_back(std::move(sf::Vector2f( 1.0f,  0.0f)));	// move to the right

	//Initializing character's speed
	const float baseSpeed = 3000000.0f;
	_speed.x = baseSpeed;
	_speed.y = baseSpeed;
}

void Character::ProcessInput(const sf::Event & /*event*/)
{
	_direction.up    = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	_direction.down  = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	_direction.left  = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	_direction.right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
}

void Character::Update(sf::Time elapsedTime)
{
	sf::Vector2f offset;
	
	if (_direction.up)		{ offset.x += _speed.x * _unitSpeedVector[0].x; offset.y += _speed.y * _unitSpeedVector[0].y; }
	if (_direction.down)	{ offset.x += _speed.x * _unitSpeedVector[1].x; offset.y += _speed.y * _unitSpeedVector[1].y; }
	if (_direction.left)	{ offset.x += _speed.x * _unitSpeedVector[2].x; offset.y += _speed.y * _unitSpeedVector[2].y; }
	if (_direction.right)	{ offset.x += _speed.x * _unitSpeedVector[3].x; offset.y += _speed.y * _unitSpeedVector[3].y; }

	_sprite.move(offset * elapsedTime.asSeconds());
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

	sf::Vector2f screenPosition;
	screenPosition.x = (windowSize.x - textureSize.x) / 2.0f;
	screenPosition.y = (windowSize.y - textureSize.y) / 2.0f;

	return screenPosition;
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