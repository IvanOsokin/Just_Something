#pragma once

// Класс BulletFactory:
// 1. Загружает и хранит:
//   - все текстуры пуль;
//   - базовые расстояния от _sprite.getOrigin() персонажа до кончика оружия
// 2. Возвращает спрайт пули в зависимости от типа оружия
// 3. Возвращает расстояния от _sprite.getOrigin() персонажа до кончика оружия в зависимости от типа оружия
// 
// При неудаче загрузки текстуры:
//	- загружаемая текстура инициализируется пустой текстурой
//  - в log-файл выводится сообщение об ошибке с указанием имени незагруженной текстуры
//  - фиксируется ошибка загрузки текстуры

class BulletFactory
{
public:
	void Init(const std::filesystem::path & resourcesDirectory, const std::vector<std::string> & bulletTextureTitle, const std::vector<float> & distanceToWeaponTip);
	
	std::optional<sf::Sprite> GetSprite(/*WeaponID*/);
	std::optional<float> GetInitPosition(/*WeaponID*/);

private:
	void LoadTextures(const std::vector<std::string> & bulletsTexturesPath);

	std::vector<sf::Texture>	_textures;
	std::vector<float>			_distanceToWeaponTip;
};