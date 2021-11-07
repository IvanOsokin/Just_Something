#pragma once

//  ласс BulletFactory:
// 1. «агружает и хранит:
//   - все текстуры пуль;
//   - базовые рассто€ни€ от _sprite.getOrigin() персонажа до кончика оружи€
// 2. ¬озвращает спрайт пули в зависимости от типа оружи€
// 3. ¬озвращает рассто€ни€ от _sprite.getOrigin() персонажа до кончика оружи€ в зависимости от типа оружи€
// 
// ѕри неудаче загрузки текстуры:
//	- загружаема€ текстура инициализируетс€ пустой текстурой
//  - в log-файл выводитс€ сообщение об ошибке с указанием имени незагруженной текстуры
//  - фиксируетс€ ошибка загрузки текстуры
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