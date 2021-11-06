#pragma once

// Класс BulletFactory:
// 1. Загружает и хранит:
//   - все текстуры пуль;
//   - базовые расстояния от центра текстуры персонажа до цончика оружия в зависимости от типа оружия
// 2. Возвращает спрайт пули в зависимости от типа оружия
// 3. Возвращает начальное положение спрайта пули в зависимости от типа оружия
// 
// При неудаче загрузки текстуры:
//	- загружаемая текстура инициализируется пустой текстурой
//  - в log-файл выводится сообщение об ошибке с указанием имени незагруженной текстуры
//  - фиксируется ошибка загрузки текстуры
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