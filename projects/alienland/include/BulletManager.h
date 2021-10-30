#pragma once

class TestScene;
class BulletFactory;

class BulletManager
{
public:
	BulletManager();

	void Init(std::shared_ptr<TestScene> testScene, const std::filesystem::path & resourcesDirectory);

private:
	std::shared_ptr<BulletFactory>  _bulletFactory;
	std::weak_ptr<TestScene>		_testScene;
	sf::IntRect						_sceneBorder;
};