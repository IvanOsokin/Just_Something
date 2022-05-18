#pragma once

namespace Utils
{
	template<typename T1, typename T2>
	sf::Vector2<T1> VectorCast(T2 x, T2 y)
	{
		return sf::Vector2<T1>(static_cast<T1>(x), static_cast<T1>(y));
	}

	template<typename T1, typename T2>
	sf::Vector2<T1> VectorCast(const sf::Vector2<T2> & vector)
	{
		return VectorCast<T1>(vector.x, vector.y);
	}

	template<typename T1, typename T2>
	sf::Rect<T1> RectCast(T2 left, T2 top, T2 width, T2 height)
	{
		return sf::Rect<T1>(static_cast<T1>(left), static_cast<T1>(top), static_cast<T1>(width), static_cast<T1>(height));
	}

	template<typename T1, typename T2>
	sf::Rect<T1> RectCast(const sf::Rect<T2> & rect)
	{
		return sf::Rect<T1>(RectCast<T1>(rect.left, rect.top, rect.width, rect.height));
	}
}