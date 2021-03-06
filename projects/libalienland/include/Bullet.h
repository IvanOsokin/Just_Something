#pragma once

#include "GameObject.h"

//  Класс Bullet:
// 1. Создает пулю и инициализирует ее:
//    - спрайтом;
//    - аналогом bbox`а в виде точек, являющихся началом и концом пули;
//    - скоростью.
//    - единичным вектором скорости, вычисленным в методе Init()
// 2. Обновляет положение пули на сцене в зависимости от времени
// 3. Отрисовывает пулю

class GameScene;

class Bullet : public GameObject
{
public:
	void Init(std::shared_ptr<GameScene> gameScene, float baseSpeed, sf::FloatRect localBounds, const sf::Vector2f & initPos, const sf::Vector2f & targetPos);

	void Update(const sf::Time & elapsedTime) override;
	void ProcessCollision() override;

private:
	void SceneBorderCollision();
	void EnemyCollision();

	sf::FloatRect				_localBounds;
	std::weak_ptr<GameScene>	_gameScene;
	sf::Vector2f				_unitSpeedVector;
	float						_baseSpeed = 0.0f;
};