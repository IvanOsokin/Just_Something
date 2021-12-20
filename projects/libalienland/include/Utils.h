#pragma once

namespace Utils
{
	const float pi = 3.141593f;

	float DegreesToRadians(float degrees);
	float RadiansToDegrees(float radians);
	float VectorLength(const sf::Vector2f & vector);
}