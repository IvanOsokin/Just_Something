#include "BulletManager.h"

#include "BulletFactory.h"
#include "Bullet.h"
#include "Enemy.h"

BulletManager::BulletManager()
	: _bulletFactory(std::make_shared<BulletFactory>())
{}

BulletManager::~BulletManager() = default;

void BulletManager::Init(const std::filesystem::path & resourcesDirectory, const sf::IntRect & sceneBorder, std::shared_ptr<Enemy> enemy)
{
	_sceneBorder = sceneBorder;
	_enemy = enemy;
	_bulletFactory->Init(resourcesDirectory, FillBulletTextureTitle(), DistanceToWeaponTip());
}

void BulletManager::AddBullet(const sf::Vector2f & currentCharacterPos, float currentCharacterRot, const sf::Vector2f & targetPos)
{
	sf::Vector2f initBulletPos = CalcInitBulletPos(currentCharacterPos, currentCharacterRot, _bulletFactory->GetInitPosition(/*WeaponID*/));

	Bullet bullet;
	const auto bulletSpeed = 200.f;
	bullet.Init(bulletSpeed, _bulletFactory->GetSprite(/*WeaponID*/), initBulletPos, targetPos);

	_bullets.emplace_back(bullet);
}

float BulletManager::GetCurrentDistFormOriginToWeaponTip(/*Weapon ID*/) const
{
	return _bulletFactory->GetInitPosition(/*Weapon ID*/);
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

	if (_enemy.lock())
	{
		EnemyCollision();
	}
}

void BulletManager::SceneBorderCollision()
{
	auto bulletsForRemoving = std::remove_if(_bullets.begin(), _bullets.end(), [*this](const Bullet & bullet)
	{
		bool shouldRemoveBullet = !_sceneBorder.contains(static_cast<int>(bullet.GetBulletBottomPosition().x),
														 static_cast<int>(bullet.GetBulletBottomPosition().y));
		return shouldRemoveBullet;
	});

	_bullets.erase(bulletsForRemoving, _bullets.end());
}

void BulletManager::EnemyCollision()
{
	if (_bullets.empty())
	{
		return;
	}

	auto enemy = _enemy.lock();

	auto currentEnemyBBox = enemy->GetBoundingBox().getGlobalBounds();
	auto bullet = _bullets.cbegin();
	bool shouldRemove = false;

	while (bullet != _bullets.cend() || shouldRemove)
	{
		shouldRemove = currentEnemyBBox.contains(static_cast<float>(bullet->GetBulletTipPosition().x),
												 static_cast<float>(bullet->GetBulletTipPosition().y));
		if (shouldRemove)
		{
			enemy->SetRemoveCondition(shouldRemove);
			break;
		}

		++bullet;
	}

	if (bullet != _bullets.cend())
	{
		_bullets.erase(bullet);
	}
}

sf::Vector2f BulletManager::CalcInitBulletPos(const sf::Vector2f & currentCharacterPos, float currentCharacterRot, float distToWeaponTip)
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

	distBetweenCharacterCenterAndWeaponTip.emplace_back(133.0f);
	distBetweenCharacterCenterAndWeaponTip.emplace_back(133.0f);

	return distBetweenCharacterCenterAndWeaponTip;
}