#pragma once

//  Класс Bullet:
// 1. Создает пулю и инициализирует ее:
//    - спрайтом;
//    - аналогом bbox`а в виде точек, являющихся началом и концом пули;
//    - скоростью.
//    - единичным вектором скорости, вычисленным в методе Init()
// 2. Обновляет положение пули на сцене в зависимости от времени
// 3. Отрисовывает пулю

class Bullet
{
public:
	void Init(const float & baseSpeed, const sf::Sprite & sprite, const sf::Vector2f & initPos, const sf::Vector2f & targetPos);

	void Update(const sf::Time & elapsedTime);
	void Render(sf::RenderTarget & renderTarget);

	const sf::Vector2f& GetBulletBottomPosition() const { return _bulletVertexes._bottom; }	// For test scene border collision 
	const sf::Vector2f& GetBulletTipPosition() const { return _bulletVertexes._tip; }		// For obstacle and enemies collision

private:
	struct CheckPoint
	{
		sf::Vector2f _tip;
		sf::Vector2f _bottom;
	}_bulletVertexes;

	sf::Sprite	 _sprite;
	sf::Vector2f _unitSpeedVector;
	float		 _baseSpeed;
};