#pragma once

class FrameProcessor
{
public:
	struct Settings
	{
		size_t			framesHistoryLength = 300;
	};
	void Init(const Settings & settings);

	void FrameStart();
	void FrameEnd();

	float CalcFramesPerSecond() const;
	std::chrono::microseconds CalcTimePerFrame() const;

private:
	using ClockType = std::chrono::system_clock;
	using Duration = ClockType::duration;
	using TimePoint = ClockType::time_point;

	struct FrameInfo
	{
		TimePoint	start;
		Duration	elapsedTime;
		bool		empty = true;
	};
	struct FrameIncompleteInfo
	{
		TimePoint	start;
	};

	void AddFrame(FrameInfo frame);

	enum class FrameByPassStatus
	{
		Continue,
		Stop
	};
	using FrameByPassCallback = std::function<FrameByPassStatus(const FrameInfo &)>;
	void ForeachFrame(const FrameByPassCallback & callback) const;

	const FrameInfo & GetFirstFrame() const;
	const FrameInfo & GetLastFrame() const;

	size_t						_frameOffset = 0;
	std::vector<FrameInfo>		_frames;
	FrameIncompleteInfo			_incompleteFrame;
};
