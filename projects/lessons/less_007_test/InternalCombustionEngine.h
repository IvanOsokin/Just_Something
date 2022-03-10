#pragma once

#include <vector>
#include <limits>
#include <filesystem>

#include "Engine.h"

class InternalCombustionEngine : public Engine
{
public:
	~InternalCombustionEngine() override = default;

	void Start(double environmentTemp, const std::filesystem::path& InitializingFilePath) override;
	void MainCycle(double time) override;

	bool IsOverheated() const override { return _engineTemperature > _engineParam._tempOverheat; }

private:
	void InitEngineParameters(double environmentTemp, const std::filesystem::path& InitializingFilePath);
	void LoadEngineParametersFromFile(const std::filesystem::path& InitializingFilePath);
	void InitVarFromString(std::vector<int>& numberOfValues, const std::string& strToParse);
	void InitVarFromString(double& number, const std::string& strToParse);
	void ConvertAndPushBack(std::vector<int>& numberOfValues, std::stringstream& strToConvert);
	void CalcCurrentMoment(int prevChartRotationValue, int nextChartRotationValue, int prevChartMomentValue, int nextChartMomentValue);

	struct EngineParameters
	{
		std::vector<int> _momentPointValues;
		std::vector<int> _rotatePointValues;

		double _tempOverheat = DBL_MIN;
		double _Hm = DBL_MIN;
		double _Hv = DBL_MIN;
		double _C = DBL_MIN;
		double _I = DBL_MIN;
	};

	EngineParameters _engineParam;

	double _currentMoment = 0.0;
	double _currentRotation = 0.0;
	double _accelaration = 0.0;
	double _tempEnvironment = DBL_MIN;
	double _engineTemperature = 0.0;

	bool _shouldStopWorking = false;
};