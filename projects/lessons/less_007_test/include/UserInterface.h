#pragma once

class UserInterface
{
public:
	void ProcessInput();
	double GetEnvironmentTemperature() const { return _environmentTemp; }
	void DisplayResult(bool wasInterrupted, double workTime);

private:
	bool IsNumber(const std::string& str);

	double _environmentTemp = 0.0;
};