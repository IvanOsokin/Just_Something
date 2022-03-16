#include "InternalCombustionEngine.h"
#include "Utils.h"

void InternalCombustionEngine::Start()
{
	
}

void InternalCombustionEngine::MainCycle(double time)
{
	const double eps = 0.001;

	static int s_currenVectorValueIndex = 0;
	static int s_nextVectorValueIndex = 1;

	if (std::fabs(_engineParam->_I - 0) < eps)
	{
		std::cout << "Incorrect engine parameters!";
		return;
	}

	_accelaration = _currentMoment / _engineParam->_I;
	_currentRotation += _accelaration * time;

	if (ShouldIncr(s_currenVectorValueIndex, s_nextVectorValueIndex))
	{
		++s_currenVectorValueIndex;
		++s_nextVectorValueIndex;
	}

	if (std::fabs(_currentRotation - _engineParam->_rotatePointValues[s_currenVectorValueIndex]) >= eps)
	{
		CalcCurrentMoment(_engineParam->_rotatePointValues[s_currenVectorValueIndex], _engineParam->_rotatePointValues[s_nextVectorValueIndex],
						  _engineParam->_momentPointValues[s_currenVectorValueIndex], _engineParam->_momentPointValues[s_nextVectorValueIndex]);
	}

	const double deltaTemperature = time * (_engineParam->_Hm * _currentMoment +
											_engineParam->_Hv * _currentRotation * _currentRotation +
											_engineParam->_C * (_tempEnvironment - _engineTemperature));

	_engineTemperature += deltaTemperature;
}

void InternalCombustionEngine::Init(double environmentTemp, const std::filesystem::path& initializingFilePath)
{
	_engineTemperature = _tempEnvironment = environmentTemp;

	_engineParam = Utils::InitEngineParameters(initializingFilePath);

	_currentMoment = _engineParam->_momentPointValues.front();
	_currentRotation = _engineParam->_rotatePointValues.front();
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

bool InternalCombustionEngine::ShouldIncr(int curValue, int nextValue)
{
	return (_currentRotation > _engineParam->_rotatePointValues[nextValue]) && (curValue < (_engineParam->_rotatePointValues.size() - 2));
}