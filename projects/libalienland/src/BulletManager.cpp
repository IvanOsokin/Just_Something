#include "BulletManager.h"

#include "BulletFactory.h"
#include "TestScene.h"

BulletManager::BulletManager()
	: _bulletFactory(std::make_shared<BulletFactory>())
{}

void BulletManager::Init(const std::filesystem::path & resourcesDirectory,
						 const sf::IntRect & sceneBorder,
						 std::shared_ptr<Enemy> enemy)
{
	_sceneBorder = sceneBorder;
	_enemy = enemy;
	_bulletFactory->Init(resourcesDirectory, FillBulletTextureTitle());
}

std::vector<std::string> BulletManager::FillBulletTextureTitle() const
{
	std::vector<std::string> bulletTextureTitle;

	bulletTextureTitle.emplace_back("bullet-0.png");
	bulletTextureTitle.emplace_back("bullet-1.png");

	return bulletTextureTitle;
}