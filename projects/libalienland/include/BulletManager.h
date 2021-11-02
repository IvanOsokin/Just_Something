#pragma once

class TestScene;
class BulletFactory;

class BulletManager
{
public:
	BulletManager();

	void Init(const sf::IntRect & sceneBorder, const std::filesystem::path & resourcesDirectory);

private:
	std::vector<std::string> FillBulletTextureTitle() const;

	std::shared_ptr<BulletFactory>  _bulletFactory;
	sf::IntRect						_sceneBorder;
};