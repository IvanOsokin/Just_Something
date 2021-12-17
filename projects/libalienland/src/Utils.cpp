#include "Utils.h"

static const float s_fromRadToDeg = 180.0f / pi;
static const float s_fromDegToRad = pi / 180.0f;


namespace Utils
{
	float DegreesToRadians(float degrees)
	{
		return 	degrees * s_fromDegToRad;
		;
	}

	float RadiansToDegrees(float radians)
	{
		return radians * s_fromRadToDeg;
	}

	float VectorLength(const sf::Vector2f & vector)
	{
		return std::powf((std::powf(vector.x, 2.0f) + std::powf(vector.y, 2.0f)), 0.5f);
	}
}