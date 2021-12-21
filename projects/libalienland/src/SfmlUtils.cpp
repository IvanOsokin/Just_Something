#include "SfmlUtils.h"

namespace Utils
{
	sf::Vector2i ToVector2i(const sf::Vector2f & vector)
	{
		return sf::Vector2i(static_cast<int>(vector.x), static_cast<int>(vector.y));
	}

	sf::Vector2f ToVector2f(const sf::Vector2i & vector)
	{
		return sf::Vector2f(static_cast<float>(vector.x), static_cast<float>(vector.y));
	}

	sf::Vector2f ToVector2f(int x, int y)
	{
		return sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
	}
}