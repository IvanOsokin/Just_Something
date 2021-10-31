#include "BulletFactory.h"

void BulletFactory::Init(const std::filesystem::path & resourcesDirectory)
{
	//std::vector<std::string> bulletTexturePath;
	//bulletTexturePath.emplace_back(std::string("bullet-0.png"));
	//bulletTexturePath.emplace_back(std::string("bullet-1.png"));

	//for (auto& iter : bulletTexturePath)
	//{
	//	auto texturePath = resourcesDirectory / iter;
	//	iter = texturePath.generic_string();
	//}

	//Assert2(LoadTexture(bulletTexturePath), "Not all textures of bullets were loaded.");

	std::vector<std::string> bulletTextureTitle;
	bulletTextureTitle.emplace_back(std::string("bullet-0.png"));
	bulletTextureTitle.emplace_back(std::string("bullet-1.png"));

	std::vector<std::string> bulletTexturePath;
	bulletTexturePath.reserve(bulletTextureTitle.size());

	for (const auto & iter : bulletTextureTitle)
	{
		auto texturePath = resourcesDirectory / iter;
		bulletTexturePath.emplace_back(texturePath.generic_string());
	}

	Assert2(LoadTexture(bulletTexturePath), "Not all textures of bullets were loaded.");
}

sf::Sprite BulletFactory::GetSprite()
{
	sf::Sprite bulletSprite;
	bulletSprite.setTexture(*_textures.begin());

	return bulletSprite;
}

bool BulletFactory::LoadTexture(const std::vector<std::string> & bulletsTexturesPath)
{
	sf::Texture texture;

	for (const auto & iter : bulletsTexturesPath)
	{
		if (!texture.loadFromFile(iter))
		{
			LOG_ERROR() << "Failed to load all the textures of bullets.";
			return false;
		}

		_textures.emplace_back(texture);
	}

	LOG_INFO() << "The bullets' textures were loaded.";
	return true;
}