#pragma once

namespace Utils
{
	template<typename T1, typename T2>
	sf::Vector2<T1> VectorCast(T2 x, T2 y)
	{
		return sf::Vector2<T1>(static_cast<T1>(x), static_cast<T1>(y));
	}

	template<typename T, typename Vector>
	sf::Vector2<T> VectorCast(const Vector & vector)
	{
		return VectorCast<T>(vector.x, vector.y);
	}
}