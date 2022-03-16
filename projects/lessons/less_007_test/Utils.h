#pragma once

#include <optional>
#include <filesystem>
#include <iostream>
#include <fstream>

#include "InternalCombustionEngine.h"

namespace Utils
{
	std::optional<EngineParameters> InitEngineParameters(const std::filesystem::path& initializingFilePath);
	bool LoadEngineParametersFromFile(EngineParameters& engineParam, const std::filesystem::path& initializingFilePath);
	void InitVarFromString(std::vector<int>& numberOfValues, const std::string& strToParse);
	void InitVarFromString(double& number, const std::string& strToParse);
	void ConvertAndPushBack(std::vector<int>& numberOfValues, std::stringstream& strToConvert);
	void DisplayResult(bool wasInterrupted, double workTime);
}