#pragma once

#include <string>

class UserInterface
{
public:
	void ProcessInput();
	double GetEnvironmentTemperature() const { return _environmentTemp; }

private:
	bool IsNumber(const std::string& str);

	double _environmentTemp = 0.0;
};