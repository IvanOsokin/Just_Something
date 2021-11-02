//  ласс BulletFactory:
// 1. «агружает и хранит все текстуры пуль;
// 2. ¬озвращает спрайт пули, соответсвующий определенным услови€м, переданным в параметры
// 
// ѕри неудаче загрузки текстуры:
//	- загружаема€ текстура инициализируетс€ пустой текстурой текстурой
//  - в log-файл выводитс€ сообщение об ошибке с указанием имени незагруженной текстуры
//  - фиксируетс€ ошибка загрузки текстуры

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