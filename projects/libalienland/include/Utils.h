#pragma once

namespace Utils
{
	const float pi = 3.141593f;

	float DegreesToRadians(float degrees);
	float RadiansToDegrees(float radians);
	float VectorLength(const sf::Vector2f & vector);

	template<typename T>
	void AppendVector(std::vector<T> && sourceVector, std::vector<T> & destinationVector)
	{
		std::move(std::make_move_iterator(sourceVector.begin()), std::make_move_iterator(sourceVector.end()), std::back_inserter(destinationVector));
	}
}