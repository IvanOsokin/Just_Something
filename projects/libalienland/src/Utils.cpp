#include "Utils.h"

namespace
{
	const float fromRadToDeg = 180.0f / Utils::pi;
	const float fromDegToRad = Utils::pi / 180.0f;
}

namespace Utils
{
	float DegreesToRadians(float degrees)
	{
		return 	degrees * fromDegToRad;
	}

	float RadiansToDegrees(float radians)
	{
		return radians * fromRadToDeg;
	}

	float VectorLength(const sf::Vector2f & vector)
	{
		return std::sqrtf((vector.x * vector.x) + (vector.y * vector.y));
	}
}