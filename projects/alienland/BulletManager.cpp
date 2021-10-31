#include "BulletManager.h"

#include "BulletFactory.h"
#include "TestScene.h"

BulletManager::BulletManager()
	: _bulletFactory(std::make_shared<BulletFactory>())
{}

void BulletManager::Init(std::shared_ptr<TestScene> testScene, const std::filesystem::path & resourcesDirectory)
{
	Assert2(testScene, "Failed to initialize BulletManger. TestScene must be created.");

	_testScene = testScene;

	auto scene = _testScene.lock();
	_sceneBorder.left   = 0;
	_sceneBorder.top    = 0;
	_sceneBorder.width  = scene->GetRenderWindow()->getSize().x;
	_sceneBorder.height = scene->GetRenderWindow()->getSize().y;
	
	_bulletFactory->Init(resourcesDirectory);
}