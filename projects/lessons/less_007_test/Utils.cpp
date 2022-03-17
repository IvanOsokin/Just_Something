#include "Utils.h"

namespace Utils
{
	std::optional<EngineParameters> InitEngineParameters(const std::filesystem::path& initializingFilePath)
	{
		EngineParameters engineParam;

		if (!LoadEngineParametersFromFile(engineParam, initializingFilePath))
		{
			return std::nullopt;
		}

		return engineParam;
	}

	bool LoadEngineParametersFromFile(EngineParameters& engineParam, const std::filesystem::path& initializingFilePath)
	{
		std::ifstream initializingFile;
		initializingFile.open(initializingFilePath.generic_string(), std::ios::in);
		
		if (!initializingFile.is_open())
		{
			std::cout << "Could not open the initializing file";
			return false;
		}

		std::string strToParse;

		std::getline(initializingFile, strToParse);
		InitVarFromString(engineParam._momentPointValues, strToParse);
		std::getline(initializingFile, strToParse);
		InitVarFromString(engineParam._rotatePointValues, strToParse);

		std::getline(initializingFile, strToParse);
		InitVarFromString(engineParam._tempOverheat, strToParse);
		std::getline(initializingFile, strToParse);
		InitVarFromString(engineParam._Hm, strToParse);
		std::getline(initializingFile, strToParse);
		InitVarFromString(engineParam._Hv, strToParse);
		std::getline(initializingFile, strToParse);
		InitVarFromString(engineParam._C, strToParse);
		std::getline(initializingFile, strToParse);
		InitVarFromString(engineParam._I, strToParse);

		initializingFile.close();

		return true;
	}

	void InitVarFromString(std::vector<int>& numberOfValues, const std::string& strToParse)
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

	void InitVarFromString(double& number, const std::string& strToParse)
	{
		std::stringstream valueToConvert;

		for (int i = 0; strToParse[i] != '\t'; ++i)
		{
			valueToConvert << strToParse[i];
		}

		valueToConvert >> number;
	}

	void ConvertAndPushBack(std::vector<int>& numberOfValues, std::stringstream& strToConvert)
	{
		int number;
		strToConvert >> number;
		numberOfValues.emplace_back(number);
		strToConvert = std::stringstream();
	}

	void Utils::DisplayResult(bool wasInterrupted, double workTime)
	{
		if (wasInterrupted)
		{
			std::cout << workTime << " seconds since the engine has started till overheated" << std::endl;
		}
		else
		{
			std::cout << "The engine examined hasn't been overheated" << std::endl;
		}
	}
}