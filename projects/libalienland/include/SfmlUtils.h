#pragma once

namespace Utils
{
	template<typename T1, typename T2>
	sf::Vector2<T1> VectorCast(const T2 & vector)
	{
		return sf::Vector2<T1>(static_cast<T1>(vector.x), static_cast<T1>(vector.y));
	}

	template<typename T1, typename T2>
	sf::Vector2<T1> VectorCast(T2 x, T2 y)
	{
		return sf::Vector2<T1>(static_cast<T1>(x), static_cast<T1>(y));
	}
}