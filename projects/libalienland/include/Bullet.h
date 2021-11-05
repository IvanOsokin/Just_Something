#pragma once

// ����� Bullet:
// 1. ������� ���� � �������������� ��:
//    - ��������;
//    - bbox`�� � ���� �����, ���������� ���������� ����;
//    - ���������.
//    - ��������� �������� ��������, ����������� � ������ Init()
// 2. ��������� ��������� ���� �� ����� � ����������� �� �������
// 3. ������������ ����
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