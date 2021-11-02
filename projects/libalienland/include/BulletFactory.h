// ����� BulletFactory:
// 1. ��������� � ������ ��� �������� ����;
// 2. ���������� ������ ����, �������������� ������������ ��������, ���������� � ���������
// 
// ��� ������� �������� ��������:
//	- ����������� �������� ���������������� ������ ��������� ���������
//  - � log-���� ��������� ��������� �� ������ � ��������� ����� ������������� ��������
//  - ����������� ������ �������� ��������

#pragma once

class BulletFactory
{
public:
	void		Init(const std::filesystem::path & resourcesDirectory, const std::vector<std::string>& bulletTextureTitle);
	sf::Sprite	GetSprite(/*Some conditions*/);

private:
	void		LoadTexture(const std::vector<std::string> & bulletsTexturesPath);

	std::vector<sf::Texture> _textures;
};