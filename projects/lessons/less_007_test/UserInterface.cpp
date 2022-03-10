#include <iostream>

#include "UserInterface.h"

void UserInterface::ProcessInput()
{
	std::string userInput;

	do
	{
		std::cout << "Please, enter the environment temperature: ";

		std::getline(std::cin, userInput);
	} while (!IsNumber(userInput));

	_environmentTemp = std::stod(userInput);
}

bool UserInterface::IsNumber(const std::string& str)
{
	if (str == "")
	{
		return false;
	}

	int floatPointCount = 0;
	int minusCount = 0;

	for (int i = 0; i < str.length(); ++i)
	{
		if (str[i] == '-' && !minusCount && !floatPointCount && i == 0)
		{
			++minusCount;
			continue;
		}

		if (str[i] == '.' && !floatPointCount)
		{
			++floatPointCount;
			continue;
		}

		if (!std::isdigit(str[i]))
		{
			return false;
		}
	}

	return true;
}