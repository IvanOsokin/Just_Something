#pragma once

// ����� BulletFactory:
// 1. ��������� � ������:
//   - ��� �������� ����;
//   - ������� ���������� �� _sprite.getOrigin() ��������� �� ������� ������
// 2. ���������� ������ ���� � ����������� �� ���� ������
// 3. ���������� ���������� �� _sprite.getOrigin() ��������� �� ������� ������ � ����������� �� ���� ������
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
	sf::Sprite	 GetSprite(/*WeaponID*/);
	float		 GetInitPosition(/*WeaponID*/);

private:
	void		LoadTextures(const std::vector<std::string> & bulletsTexturesPath);

	std::vector<sf::Texture>	_textures;
	std::vector<float>			_distanceToWeaponTip;		// Distance between the center of the character sprite and the tip of the weapon
};