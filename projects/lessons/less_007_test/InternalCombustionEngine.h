#pragma once

#include <vector>
#include "Engine.h"

struct EngineParameters
{
	std::vector<int> _momentPointValues;
	std::vector<int> _rotatePointValues;

	double _tempOverheat = 0.0;
	double _Hm = 0.0;
	double _Hv = 0.0;
	double _C = 0.0;
	double _I = 0.0;
};

class InternalCombustionEngine : public Engine
{
public:
	InternalCombustionEngine() {};

	~InternalCombustionEngine() override = default;

	void Start() override;
	void MainCycle(double time) override;
	void Init(double environmentTemp, const std::filesystem::path& initializingFilePath);

	bool IsOverheated() const override { return _engineTemperature > _engineParam->_tempOverheat; }

private:
	void CalcCurrentMoment(int prevChartRotationValue, int nextChartRotationValue, int prevChartMomentValue, int nextChartMomentValue);
	bool ShouldIncr(int curValue, int nextValue);

	std::optional<EngineParameters> _engineParam;

	double _currentMoment = 0.0;
	double _currentRotation = 0.0;
	double _accelaration = 0.0;
	double _tempEnvironment = 0.0;
	double _engineTemperature = 0.0;

	bool _shouldStopWorking = false;
};