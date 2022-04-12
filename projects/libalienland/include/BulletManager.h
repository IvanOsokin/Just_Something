#pragma once

class Bullet;
class BulletFactory;
class GameScene;

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	void Init(const std::filesystem::path & resourcesDirectory);

	std::shared_ptr<Bullet> CreateBullet(std::shared_ptr<GameScene> gameScene, const sf::Vector2f & curCharPos, float curCharRot, const sf::Vector2f & targetPos);
	float GetCurrentDistFormOriginToWeaponTip(/*Weapon ID*/) const;

	void Update(const sf::Time & elapsedTime);
	void Render(sf::RenderTarget & renderTarget);

private:
	sf::Vector2f CalcInitBulletPos(const sf::Vector2f & currentCharacterPos, float currentCharacterRot, float distToWeaponTip);

	std::vector<std::string> FillBulletTextureTitle() const;
	std::vector<float> DistanceToWeaponTip() const;

	std::shared_ptr<BulletFactory>		_bulletFactory;
};