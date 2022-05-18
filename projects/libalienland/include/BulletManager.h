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

// #include "Character.h"
// #include "Enemy.h"

// class Spawner;
//
// class World
// {
// public:
// 	void Update();
// 	void SetSpawner(std::unique_ptr<Spawner> spawner)
// 	{
// 		_spawner = std::move(spawner);
// 	}
//
// private:
// 	std::unique_ptr<Spawner> _spawner;
// 	std::vector<std::shared_ptr<GameObject>> _gameObjects;
// };
//
// class WorldFactory
// {
// public:
// 	virtual ~WorldFactory() = default;
// 	virtual std::shared_ptr<World> Create() = 0;
// };
//
// class GameObject;
// class Spawner
// {
// public:
// 	virtual ~Spawner() = default;
// 	virtual std::vector<std::shared_ptr<GameObject>> Spawn() = 0;
// };
//
// class TestEnemySpawner : public Spawner
// {
// public:
// 	std::vector<std::shared_ptr<GameObject>> Spawn() override
// 	{
// 		if (_spawned)
// 		{
// 			return {};
// 		}
// 		_spawned = true;
// 		return {
// 			std::make_shared<Enemy>()
// 		};
// 	}
//
// private:
// 	bool		_spawned = false;
// };
//
// class TestCharacterSpawner : public Spawner
// {
// public:
// 	std::vector<std::shared_ptr<GameObject>> Spawn() override
// 	{
// 		if (_spawned)
// 		{
// 			return {};
// 		}
// 		_spawned = true;
// 		return {
// 			std::make_shared<Character>()
// 		};
// 	}
//
// private:
// 	bool		_spawned = false;
// };
//
// class TestSpawner : public Spawner
// {
// public:
// 	TestSpawner(std::unique_ptr<Spawner> playerSpawner, std::unique_ptr<Spawner> enemiesSpawner);
// 	std::vector<std::shared_ptr<GameObject>> Spawn() override
// 	{
// 		auto players = _playerSpawner->Spawn();
// 		auto enemies = _enemiesSpawner->Spawn();
// 		
// 		std::vector<std::shared_ptr<GameObject>> allObjects;
// 		std::move(std::make_move_iterator(players.begin()), std::make_move_iterator(players.end()), std::back_inserter(allObjects));
// 		std::move(std::make_move_iterator(enemies.begin()), std::make_move_iterator(enemies.end()), std::back_inserter(allObjects));
// 		return allObjects;
// 	}
//
// 	std::unique_ptr<Spawner> _playerSpawner;
// 	std::unique_ptr<Spawner> _enemiesSpawner;
// };
//
// inline void World::Update()
// {
// 	auto spawnedEntities = _spawner->Spawn();
// 	std::move(std::make_move_iterator(spawnedEntities.begin()), std::make_move_iterator(spawnedEntities.end()), std::back_inserter(_gameObjects));
// }
//
// class TestWorldFactory : public WorldFactory
// {
// public:
// 	std::shared_ptr<World> Create() override
// 	{
// 		auto world = std::make_shared<World>();
//
// 		auto playerSpawner = std::make_unique<TestCharacterSpawner>();
// 		auto enemySpawner = std::make_unique<TestEnemySpawner>();
// 		
// 		auto allSpawner = std::make_unique<TestSpawner>(std::move(playerSpawner), std::move(enemySpawner));
// 		world->SetSpawner(std::move(allSpawner));
// 		return world;
// 	}
// };