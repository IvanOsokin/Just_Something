#include "BulletManager.h"

#include "BulletFactory.h"
#include "Bullet.h"
#include "Enemy.h"

BulletManager::BulletManager()
	: _bulletFactory(std::make_shared<BulletFactory>())
{}

BulletManager::~BulletManager() = default;

void BulletManager::Init(const std::filesystem::path & resourcesDirectory,
						 const sf::IntRect & sceneBorder,
						 std::shared_ptr<Enemy> enemy)
{
	_sceneBorder = sceneBorder;
	_enemy = enemy;
	_bulletFactory->Init(resourcesDirectory, FillBulletTextureTitle(), DistanceToWeaponTip());
}

void BulletManager::AddBullet(const sf::Vector2f & currentCharacterPos, const float & currentCharacterRot, const sf::Vector2f & targetPos)
{
	sf::Vector2f initBulletPos = CalcInitBulletPos(currentCharacterPos, currentCharacterRot, _bulletFactory->GetInitPosition(/*WeaponID*/));

	// Make bullet speed storage
	Bullet bullet(2000.0f, _bulletFactory->GetSprite(/*WeaponID*/));

	bullet.Init(initBulletPos, targetPos);

	_bullets.emplace_back(bullet);
}

void BulletManager::Update(const sf::Time & elapsedTime)
{
	for (auto & bullet : _bullets)
	{
		bullet.Update(elapsedTime);
	}

	ProcessCollision();
}

void BulletManager::Render(sf::RenderTarget & renderTarget)
{
	for (auto & bullet : _bullets)
	{
		bullet.Render(renderTarget);
	}
}

void BulletManager::ProcessCollision()
{
	SceneBorderCollision();
	EnemyCollision();
}

void BulletManager::SceneBorderCollision()
{
	_bullets.erase(std::remove_if(_bullets.begin(),
								  _bullets.end(),
								  [*this](const Bullet & bullet)
								  {
				   					  return !_sceneBorder.contains(static_cast<int>(bullet.GetBulletBottomPosition().x),
				   													static_cast<int>(bullet.GetBulletBottomPosition().y));}),
				  _bullets.end());
}

void BulletManager::EnemyCollision()
{

}

sf::Vector2f BulletManager::CalcInitBulletPos(const sf::Vector2f & currentCharacterPos,
											  const float & currentCharacterRot,
											  const float & distToWeaponTip)
{
	const float pi = 3.141593f;
	static const float s_fromDegToRad = pi / 180.0f;

	sf::Vector2f tipWeaponPosition;
	tipWeaponPosition.x = distToWeaponTip * std::cosf(currentCharacterRot * s_fromDegToRad);
	tipWeaponPosition.y = distToWeaponTip * std::sinf(currentCharacterRot * s_fromDegToRad);

	return currentCharacterPos + tipWeaponPosition;
}

std::vector<std::string> BulletManager::FillBulletTextureTitle() const
{
	std::vector<std::string> bulletTextureTitle;

	bulletTextureTitle.emplace_back("bullet-0.png");
	bulletTextureTitle.emplace_back("bullet-1.png");

	return bulletTextureTitle;
}

std::vector<float> BulletManager::DistanceToWeaponTip() const
{
	std::vector<float> distBetweenCharacterCenterAndWeaponTip;

	distBetweenCharacterCenterAndWeaponTip.emplace_back(122.33f);
	distBetweenCharacterCenterAndWeaponTip.emplace_back(122.33f);

	return distBetweenCharacterCenterAndWeaponTip;
}