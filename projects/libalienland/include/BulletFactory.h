#pragma once

// ����� BulletFactory:
// 1. ��������� � ������:
//   - ��� �������� ����;
//   - ������� ���������� �� ������ �������� ��������� �� ������� ������ � ����������� �� ���� ������
// 2. ���������� ������ ���� � ����������� �� ���� ������
// 3. ���������� ��������� ��������� ������� ���� � ����������� �� ���� ������
// 
// ��� ������� �������� ��������:
//	- ����������� �������� ���������������� ������ ���������
//  - � log-���� ��������� ��������� �� ������ � ��������� ����� ������������� ��������
//  - ����������� ������ �������� ��������
class BulletFactory
{
public:
	void		 Init(const std::filesystem::path & resourcesDirectory,
					  const std::vector<std::string> & bulletTextureTitle,
					  const std::vector<float> & distanceToWeaponTip);
	sf::Sprite	 GetSprite(/*Depending on WeaponID*/);
	sf::Vector2f GetInitPosition(/*Depending on WeaponID,*/ const sf::Vector2f & characterPos, const float & angle);

private:
	void		LoadTextures(const std::vector<std::string> & bulletsTexturesPath);

	std::vector<sf::Texture>	_textures;
	std::vector<float>			_distanceToWeaponTip;		// Distance between the center of the character sprite and the tip of the weapon
};