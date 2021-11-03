#pragma once

// ����� BulletFactory:
// 1. ��������� � ������ ��� �������� ����;
// 2. ���������� ������ ����, �������������� ������������ ��������, ���������� � ���������
// 
// ��� ������� �������� ��������:
//	- ����������� �������� ���������������� ������ ��������� ���������
//  - � log-���� ��������� ��������� �� ������ � ��������� ����� ������������� ��������
//  - ����������� ������ �������� ��������
class BulletFactory
{
public:
	void		Init(const std::filesystem::path & resourcesDirectory, const std::vector<std::string>& bulletTextureTitle);
	sf::Sprite	GetSprite(/*Some conditions*/);

private:
	void		LoadTextures(const std::vector<std::string> & bulletsTexturesPath);

	std::vector<sf::Texture> _textures;
};