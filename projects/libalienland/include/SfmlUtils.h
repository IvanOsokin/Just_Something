#pragma once

namespace Utils
{
	sf::Vector2i ToVector2i(const sf::Vector2f & vector);
	sf::Vector2f ToVector2f(const sf::Vector2i & vector);
	sf::Vector2f ToVector2f(int x, int y);
}