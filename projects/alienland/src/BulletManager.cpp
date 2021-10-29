#include "BulletManager.h"

#include "BulletFactory.h"

BulletManager::BulletManager()
	: _bulletFactory(std::make_shared<BulletFactory>())
{}

void BulletManager::Init(const std::filesystem::path & resourcesDirectory)
{
	_bulletFactory->Init(resourcesDirectory);
}