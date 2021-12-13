#include "BulletFactory.h"

void BulletFactory::Init(const std::filesystem::path & resourcesDirectory,
						 const std::vector<std::string> & bulletTextureTitle,
						 const std::vector<float> & distanceToWeaponTip)
{
	_distanceToWeaponTip = distanceToWeaponTip;

	std::vector<std::string> bulletTexturePath;
	bulletTexturePath.reserve(bulletTextureTitle.size());

	for (const auto & textureTitle : bulletTextureTitle)
	{
		auto texturePath = resourcesDirectory / textureTitle;
		bulletTexturePath.emplace_back(texturePath.generic_string());
	}

	LoadTextures(bulletTexturePath);
}

std::optional<sf::Sprite> BulletFactory::GetSprite(/*WeaponID*/)
{
	if (_textures.empty())
	{
		LOG_ERROR() << "Cannot get access to bullets textures.";
		return std::nullopt;
	}

	sf::Sprite bulletSprite;
	bulletSprite.setTexture(*_textures.begin());

	return bulletSprite;
}

std::optional<float> BulletFactory::GetInitPosition(/*WeaponID*/)
{
	if (_distanceToWeaponTip.empty())
	{
		LOG_ERROR() << "Cannot get access to bullets distance to weapon tip.";
		return std::nullopt;
	}

	return *_distanceToWeaponTip.begin();
}

void BulletFactory::LoadTextures(const std::vector<std::string> & bulletsTexturesPath)
{
	std::size_t count = 0;
	bool isSuccess = true;

	for (const auto & texturePath : bulletsTexturesPath)
	{
		sf::Texture texture;

		if (!texture.loadFromFile(texturePath))
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