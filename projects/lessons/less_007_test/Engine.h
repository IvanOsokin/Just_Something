#pragma once

#include <filesystem>

class Engine
{
public:
	virtual ~Engine() = default;

	virtual void Start() {}
	virtual void MainCycle(double time) {}
	virtual bool IsOverheated() const { return true; }
};