#pragma once

class TestScene;
class Enemy;
class BulletFactory;

class BulletManager
{
public:
	BulletManager();

	void Init(const std::filesystem::path & resourcesDirectory,
			  const sf::IntRect & sceneBorder,
			  std::shared_ptr<Enemy> enemy);

private:
	std::vector<std::string> FillBulletTextureTitle() const;

	std::shared_ptr<BulletFactory>  _bulletFactory;
	std::shared_ptr<Enemy>			_enemy;
	sf::IntRect						_sceneBorder;
};