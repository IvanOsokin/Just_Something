#pragma once

//  ласс Bullet:
// 1. —оздает пулю и инициализирует ее:
//    - спрайтом;
//    - bbox`ом в виде точек, образующих наконечник пули;
//    - скоростью.
//    - единичным вектором скорости, вычисленным в методе Init()
// 2. ќбновл€ет положение пули на сцене в зависимости от времени
// 3. ќтрисовывает пулю
class Bullet
{
public:
	Bullet(const float & baseSpeed, const sf::Sprite & sprite, const sf::VertexArray & bulletBoundingBoxes);
	~Bullet();

	void Init(const sf::Vector2f & initPos, const sf::Vector2f & targetPos);

	void Update(const sf::Time & elapsedTime);
	void Render(sf::RenderTarget & renderTarget);

private:
	sf::Sprite		_sprite;
	sf::VertexArray	_boundingBoxes;
	sf::Vector2f	_unitSpeedVector;
	const float		_baseSpeed;
};