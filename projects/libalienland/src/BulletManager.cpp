#include "BulletManager.h"

#include "BulletFactory.h"
#include "TestScene.h"

BulletManager::BulletManager()
	: _bulletFactory(std::make_shared<BulletFactory>())
{}

void BulletManager::Init(const sf::IntRect & sceneBorder, const std::filesystem::path & resourcesDirectory)
{
	_sceneBorder = sceneBorder;

	_bulletFactory->Init(resourcesDirectory, FillBulletTextureTitle());
}

std::vector<std::string> BulletManager::FillBulletTextureTitle() const
{
	std::vector<std::string> bulletTextureTitle;

	bulletTextureTitle.emplace_back(std::string("bullet-0.png"));
	bulletTextureTitle.emplace_back(std::string("bullet-1.png"));

	return bulletTextureTitle;
}