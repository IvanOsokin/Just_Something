#pragma once

class Enemy;
class Bullet;
class BulletFactory;

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	void Init(const std::filesystem::path & resourcesDirectory, const sf::IntRect & sceneBorder, std::shared_ptr<Enemy> enemy);

	void AddBullet(const sf::Vector2f & currentCharacterPos, float currentCharacterRot, const sf::Vector2f & targetPos);

	void Update (const sf::Time & elapsedTime);
	void Render (sf::RenderTarget & renderTarget);

private:
	void ProcessCollision();
	void SceneBorderCollision();
	void EnemyCollision();

	sf::Vector2f CalcInitBulletPos(const sf::Vector2f & currentCharacterPos, float currentCharacterRot, float distToWeaponTip);

	std::vector<std::string> FillBulletTextureTitle() const;
	std::vector<float> DistanceToWeaponTip() const;

	std::shared_ptr<BulletFactory> _bulletFactory;
	std::shared_ptr<Enemy> _enemy;

	std::vector<Bullet> _bullets;

	sf::IntRect _sceneBorder;
};