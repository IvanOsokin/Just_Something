#pragma once

// ����� Bullet:
// 1. ������� ���� � �������������� ��:
//    - ��������;
//    - �������� bbox`� � ���� �����, ���������� ������� � ������ ����;
//    - ���������.
//    - ��������� �������� ��������, ����������� � ������ Init()
// 2. ��������� ��������� ���� �� ����� � ����������� �� �������
// 3. ������������ ����

struct CheckPoint
{
	sf::Vector2f _tip;
	sf::Vector2f _bottom;
};

class Bullet
{
public:
	Bullet(const float & baseSpeed, const sf::Sprite & sprite);
	~Bullet();

	Bullet& operator= (const Bullet & bullet);

	void Init(const sf::Vector2f & initPos, const sf::Vector2f & targetPos);

	void Update(const sf::Time & elapsedTime);
	void Render(sf::RenderTarget & renderTarget);

	const sf::Vector2f& GetBulletBottomPosition() const { return _bulletVertexes._bottom; }
	const sf::Vector2f& GetBulletTipPosition() const { return _bulletVertexes._tip; }

private:
	sf::Sprite	 _sprite;
	CheckPoint	 _bulletVertexes;
	sf::Vector2f _unitSpeedVector;
	float		 _baseSpeed;
};