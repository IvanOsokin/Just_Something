#pragma once

#include <filesystem>

class Engine
{
public:
	virtual ~Engine() = default;

	virtual void Start(double environmentTemp, const std::filesystem::path& InitializingFilePath) {}
	virtual void MainCycle(double time) {}
	virtual bool IsOverheated() const { return true; }
};