#include <iostream>
#include <fstream>

#include "InternalCombustionEngine.h"

void InternalCombustionEngine::Start(double environmentTemp, const std::filesystem::path& InitializingFilePath)
{
	InitEngineParameters(environmentTemp, InitializingFilePath);
}

void InternalCombustionEngine::MainCycle(double time)
{
	const double eps = 0.001;

	static int s_currenVectorValueIndex = 0;
	static int s_nextVectorValueIndex = 1;

	if (std::fabs(_engineParam._I - 0) < eps)
	{
		std::cout << "Incorrect engine parameters!";
		return;
	}

	_accelaration = _currentMoment / _engineParam._I;
	_currentRotation += _accelaration * time;

	if ((_currentRotation > _engineParam._rotatePointValues[s_nextVectorValueIndex]) &&
		(s_currenVectorValueIndex < (_engineParam._rotatePointValues.size() - 2)))
	{
		++s_currenVectorValueIndex;
		++s_nextVectorValueIndex;
	}

	if (std::fabs(_currentRotation - _engineParam._rotatePointValues[s_currenVectorValueIndex]) >= eps)
	{
		CalcCurrentMoment(_engineParam._rotatePointValues[s_currenVectorValueIndex], _engineParam._rotatePointValues[s_nextVectorValueIndex],
						  _engineParam._momentPointValues[s_currenVectorValueIndex], _engineParam._momentPointValues[s_nextVectorValueIndex]);
	}

	const double deltaTemperature = time * (_engineParam._Hm * _currentMoment +
											_engineParam._Hv * _currentRotation * _currentRotation +
											_engineParam._C * (_tempEnvironment - _engineTemperature));

	_engineTemperature += deltaTemperature;
}

void InternalCombustionEngine::InitEngineParameters(double environmentTemp, const std::filesystem::path& InitializingFilePath)
{
	_engineTemperature = _tempEnvironment = environmentTemp;

	LoadEngineParametersFromFile(InitializingFilePath);

	_currentMoment = _engineParam._momentPointValues.front();
	_currentRotation = _engineParam._rotatePointValues.front();
}

void InternalCombustionEngine::LoadEngineParametersFromFile(const std::filesystem::path& InitializingFilePath)
{
	std::ifstream engineParam;
	engineParam.open(InitializingFilePath.generic_string(), std::ios::in);

	if (!engineParam.is_open())
	{
		std::cout << "Couldn't open the initializing file";
		return;
	}

	std::string strToParse;

	std::getline(engineParam, strToParse);
	InitVarFromString(_engineParam._momentPointValues, strToParse);
	std::getline(engineParam, strToParse);
	InitVarFromString(_engineParam._rotatePointValues, strToParse);

	std::getline(engineParam, strToParse);
	InitVarFromString(_engineParam._tempOverheat, strToParse);
	std::getline(engineParam, strToParse);
	InitVarFromString(_engineParam._Hm, strToParse);
	std::getline(engineParam, strToParse);
	InitVarFromString(_engineParam._Hv, strToParse);
	std::getline(engineParam, strToParse);
	InitVarFromString(_engineParam._C, strToParse);
	std::getline(engineParam, strToParse);
	InitVarFromString(_engineParam._I, strToParse);

	engineParam.close();
}

void InternalCombustionEngine::InitVarFromString(std::vector<int>& numberOfValues, const std::string& strToParse)
{
	std::stringstream valueToConvert;
	
	int i = 0;

	for (; strToParse[i] != '\t'; ++i)
	{
		if (strToParse[i] == ' ')
		{
			ConvertAndPushBack(numberOfValues, valueToConvert);
			continue;
		}
		valueToConvert << strToParse[i];
	}
	ConvertAndPushBack(numberOfValues, valueToConvert);
}

void InternalCombustionEngine::InitVarFromString(double& number, const std::string& strToParse)
{
	std::stringstream valueToConvert;

	for (int i = 0; strToParse[i] != '\t'; ++i)
	{
		valueToConvert << strToParse[i];
	}

	valueToConvert >> number;
}

void InternalCombustionEngine::ConvertAndPushBack(std::vector<int>& numberOfValues, std::stringstream& strToConvert)
{
	int number = 0;

	strToConvert >> number;
	numberOfValues.emplace_back(number);
	strToConvert = std::stringstream();
}

void InternalCombustionEngine::CalcCurrentMoment(int prevChartRotationValue,
												 int nextChartRotationValue,
												 int prevChartMomentValue,
												 int nextChartMomentValue)
{
	if (prevChartRotationValue == nextChartRotationValue)
	{
		return;
	}

	_currentMoment = (_currentRotation - static_cast<double>(prevChartRotationValue)) *
					 (nextChartMomentValue - static_cast<double>(prevChartMomentValue)) /
					 (nextChartRotationValue - static_cast<double>(prevChartRotationValue)) + prevChartMomentValue;
}