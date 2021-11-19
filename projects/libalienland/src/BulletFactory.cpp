#include "BulletFactory.h"

void BulletFactory::Init(const std::filesystem::path & resourcesDirectory,
						 const std::vector<std::string> & bulletTextureTitle,
						 const std::vector<float> & distanceToWeaponTip)
{
	_distanceToWeaponTip = distanceToWeaponTip;

	std::vector<std::string> bulletTexturePath;
	bulletTexturePath.reserve(bulletTextureTitle.size());

	for (const auto & iter : bulletTextureTitle)
	{
		auto texturePath = resourcesDirectory / iter;
		bulletTexturePath.emplace_back(texturePath.generic_string());
	}

	LoadTextures(bulletTexturePath);
}

sf::Sprite BulletFactory::GetSprite(/*WeaponID*/)
{
	sf::Sprite bulletSprite;
	bulletSprite.setTexture(*_textures.begin());

	return bulletSprite;
}

float BulletFactory::GetInitPosition(/*WeaponID*/)
{
	return *_distanceToWeaponTip.begin();
}

void BulletFactory::LoadTextures(const std::vector<std::string> & bulletsTexturesPath)
{
	std::size_t count = 0;
	bool isSuccess = true;

	for (const auto & iter : bulletsTexturesPath)
	{
		sf::Texture texture;

		if (!texture.loadFromFile(iter))
		{
			// Прикрутить std::error_code
			LOG_ERROR() << "Failed to load the \"bullet-" << count << ".png\" texture.";
			isSuccess = false;
		}

		_textures.emplace_back(texture);

		++count;
	}

	if (isSuccess)
	{
		LOG_INFO() << "Successful loading of textures of bullets.";
	}
}