#pragma once

class BulletFactory
{
public:
	void		Init(const std::filesystem::path & resourcesDirectory);
	sf::Sprite	GetSprite();

private:
	bool		LoadTexture(const std::vector<std::string> & bulletsTexturesPath);

	std::vector<sf::Texture> _textures;
};