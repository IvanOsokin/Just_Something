#pragma once

class FrameProcessor
{
public:
	using ClockType = std::chrono::system_clock;
	using Duration = ClockType::duration;
	using TimePoint = ClockType::time_point;

	void ResetHistory(size_t historyLength);

	void FrameStart();
	void FrameEnd();

	void RecalculateFramesPerSecond();
	void RecalculateTimePerFrame();

	float GetFramesPerSecond() const;
	std::chrono::microseconds GetTimePerFrame() const;

	struct FrameInfo
	{
		TimePoint	start;
		Duration	elapsedTime;
	};
	enum class FrameByPassStatus
	{
		Continue,
		Stop
	};
	using FrameByPassCallback = std::function<FrameByPassStatus(const FrameInfo &)>;

	/**
	 * \brief Iteration by ready frames. If no frames are ready, callback won't be called.
	 */
	void ForeachFrame(const FrameByPassCallback & callback) const;

private:
	struct FrameIncompleteInfo
	{
		TimePoint	start;
	};
	struct CachedCalculations
	{
		float							fps = 0.0f;
		std::chrono::microseconds		tps {};
	};

	void AddFrame(FrameInfo frame);

	size_t						_frameStart = 0;
	size_t						_frameEnd = 0;
	std::vector<FrameInfo>		_frames;
	FrameIncompleteInfo			_incompleteFrame;
	CachedCalculations			_cache;
};
