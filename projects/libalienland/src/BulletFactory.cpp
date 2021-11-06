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

sf::Sprite BulletFactory::GetSprite(/*Depending on WeaponID*/)
{
	sf::Sprite bulletSprite;
	bulletSprite.setTexture(*_textures.begin());

	return bulletSprite;
}

sf::Vector2f BulletFactory::GetInitPosition(/*Depending on WeaponID,*/ const sf::Vector2f & characterPos, const float & angle)
{
	const float pi = 3.141593f;
	static const float s_fromRadToDeg = 180.0f / pi;

	sf::Vector2f tipWeaponPosition;
	tipWeaponPosition.x = (*_distanceToWeaponTip.begin()) * std::cosf(angle) * s_fromRadToDeg;
	tipWeaponPosition.y = (*_distanceToWeaponTip.begin()) * std::sinf(angle) * s_fromRadToDeg;

	return characterPos + tipWeaponPosition;
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