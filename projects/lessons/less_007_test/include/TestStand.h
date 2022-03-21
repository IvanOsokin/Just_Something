#pragma once

class Engine;

class TestStand
{
public:
	void Start(std::shared_ptr<Engine> testEngine);
	double GetWorkTime() const { return _workTime; }
	bool WasInterrupted() const { return _wasInterrupted; }

private:
	void MainCycle(std::shared_ptr<Engine> testEngine);

	double _workTime = 0.0;
	bool _wasInterrupted = false;
};