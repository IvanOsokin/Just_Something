#include "InternalCombustionEngine.h"
#include "Utils.h"

void InternalCombustionEngine::Start()
{
	
}

void InternalCombustionEngine::MainCycle(double time)
{
	const double eps = 0.001;

	if (std::fabs(_engineParam->_I - 0) < eps)
	{
		std::cout << "Incorrect engine parameters!";
		return;
	}

	_accelaration = _currentMoment / _engineParam->_I;
	_currentRotation += _accelaration * time;

	if (ShouldIncr())
	{
		++_currenVectorIndex;
		++_nextVectorIndex;
	}

	if (std::fabs(_currentRotation - _engineParam->_rotatePointValues[_currenVectorIndex]) >= eps)
	{
		CalcCurrentMoment(_engineParam->_rotatePointValues[_currenVectorIndex], _engineParam->_rotatePointValues[_nextVectorIndex],
						  _engineParam->_momentPointValues[_currenVectorIndex], _engineParam->_momentPointValues[_nextVectorIndex]);
	}

	const double deltaTemperature = time * (_engineParam->_Hm * _currentMoment +
											_engineParam->_Hv * _currentRotation * _currentRotation +
											_engineParam->_C * (_tempEnvironment - _engineTemperature));

	_engineTemperature += deltaTemperature;
}

bool InternalCombustionEngine::Init(double environmentTemp, const std::filesystem::path& initializingFilePath)
{
	_engineParam = Utils::InitEngineParameters(initializingFilePath);

	if (!_engineParam)
	{
		return false;
	}

	_engineTemperature = _tempEnvironment = environmentTemp;
	_currentMoment = _engineParam->_momentPointValues.front();
	_currentRotation = _engineParam->_rotatePointValues.front();

	return true;
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

bool InternalCombustionEngine::ShouldIncr()
{
	return (_currentRotation > _engineParam->_rotatePointValues[_nextVectorIndex]) &&
		   (_currenVectorIndex < (_engineParam->_rotatePointValues.size() - 2));
}