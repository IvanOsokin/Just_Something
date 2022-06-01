#include "BulletManager.h"

#include "BulletFactory.h"
#include "Bullet.h"
#include "Utils.h"
#include "Render/SimpleSpriteUnitRender.h"

BulletManager::BulletManager(sf::RenderTarget& renderTarget)
	: _bulletFactory(std::make_shared<BulletFactory>())
	, _renderTarget(renderTarget)
{
}

BulletManager::~BulletManager() = default;

void BulletManager::Init(const std::filesystem::path & resourcesDirectory)
{
	_bulletFactory->Init(resourcesDirectory, FillBulletTextureTitle(), DistanceToWeaponTip());
}

std::shared_ptr<Bullet> BulletManager::CreateBullet(std::shared_ptr<GameScene> gameScene, const sf::Vector2f & curCharPos, float curCharRot, const sf::Vector2f & targetPos)
{
	auto initPosition = _bulletFactory->GetInitPosition(/*WeaponID*/);
	sf::Vector2f initBulletPos = CalcInitBulletPos(curCharPos, curCharRot, initPosition.value_or(0.0f));
	const auto bulletSpeed = 200.f;
	auto bulletSprite = _bulletFactory->GetSprite(/*WeaponID*/);
	auto bullet = std::make_shared<Bullet>();

	sf::FloatRect bulletBounds;
	if (bulletSprite)
	{
		bulletBounds = bulletSprite->getLocalBounds();
	}
	bullet->Init(gameScene, bulletSpeed, bulletBounds, initBulletPos, targetPos);

	if (bulletSprite)
	{
		auto render = std::make_unique<SimpleSpriteUnitRender>(_renderTarget, *bulletSprite, bullet->Transform());
		bullet->SetRender(std::move(render));
	}
	
	return bullet;
}

float BulletManager::GetCurrentDistFormOriginToWeaponTip(/*Weapon ID*/) const
{
	return _bulletFactory->GetInitPosition(/*Weapon ID*/).value_or(0.0f);
}

sf::Vector2f BulletManager::CalcInitBulletPos(const sf::Vector2f & currentCharacterPos, float currentCharacterRot, float distToWeaponTip)
{
	sf::Vector2f tipWeaponPosition;
	tipWeaponPosition.x = distToWeaponTip * std::cosf(Utils::DegreesToRadians(currentCharacterRot));
	tipWeaponPosition.y = distToWeaponTip * std::sinf(Utils::DegreesToRadians(currentCharacterRot));

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

	distBetweenCharacterCenterAndWeaponTip.emplace_back(79.0f);
	distBetweenCharacterCenterAndWeaponTip.emplace_back(79.0f);

	return distBetweenCharacterCenterAndWeaponTip;
}