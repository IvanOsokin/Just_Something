#include "Imgui/Impl/FrameProcessor.h"

void FrameProcessor::Init(const Settings& settings)
{
	_frames.resize(settings.framesHistoryLength);
}

void FrameProcessor::FrameStart()
{
	_incompleteFrame.start = ClockType::now();
}

void FrameProcessor::FrameEnd()
{
	FrameInfo frame;
	frame.empty = false;
	frame.start = _incompleteFrame.start;
	frame.elapsedTime = ClockType::now() - _incompleteFrame.start;

	AddFrame(std::move(frame));
}

float FrameProcessor::CalcFramesPerSecond() const
{
	bool firstFrame = true;
	TimePoint firstFrameStart;
	TimePoint lastFrameStart;
	size_t frames = 0;
	FrameByPassCallback callback = [&](const FrameInfo & frame)
	{
		if (firstFrame)
		{
			firstFrameStart = frame.start;
			firstFrame = false;
		}
		lastFrameStart = frame.start;
		frames += 1;
		return FrameByPassStatus::Continue;
	};
	ForeachFrame(callback);

	const Duration allFramesDuration = lastFrameStart - firstFrameStart;
	if (allFramesDuration <= Duration::zero())
	{
		return 0.0f;
	}

	using PrecisionType = std::chrono::microseconds;
	const auto duration = std::chrono::duration_cast<PrecisionType>(allFramesDuration).count();
	const double seconds = duration / static_cast<double>(PrecisionType::period::den);

	return static_cast<float>(frames / seconds);
}

std::chrono::microseconds FrameProcessor::CalcTimePerFrame() const
{
	double seconds = 0.0;
	size_t frames = 0;
	FrameByPassCallback callback = [&](const FrameInfo & frame)
	{
		seconds += frame.elapsedTime.count() / static_cast<double>(Duration::period::den);
		frames += 1;
		return FrameByPassStatus::Continue;
	};
	ForeachFrame(callback);

	if (frames != 0)
	{
		const auto mcs = static_cast<uint64_t>(seconds * 1'000'000);
		return std::chrono::microseconds(mcs) / frames;
	}
	return std::chrono::microseconds::zero();
}

void FrameProcessor::AddFrame(FrameInfo frame)
{
	_frames[_frameOffset] = std::move(frame);
	_frameOffset = (_frameOffset + 1) % _frames.size();
}

void FrameProcessor::ForeachFrame(const FrameByPassCallback& callback) const
{
	auto ProcessIteration = [&](size_t frameOffset)
	{
		const auto & frame = _frames[frameOffset];
		auto status = FrameByPassStatus::Stop;
		if (!frame.empty)
		{
			status = callback(frame);
		}
		return status;
	};

	auto byPassSatus = FrameByPassStatus::Continue;
	for (size_t frameOffset = _frameOffset; 
		frameOffset < _frames.size() && byPassSatus != FrameByPassStatus::Stop; 
		++frameOffset)
	{
		byPassSatus = ProcessIteration(frameOffset);
	}

	if (_frameOffset == 0)
	{
		return;
	}

	for (size_t frameOffset = 0; 
		frameOffset < _frameOffset && byPassSatus != FrameByPassStatus::Stop; 
		++frameOffset)
	{
		byPassSatus = ProcessIteration(frameOffset);
	}
}

const FrameProcessor::FrameInfo& FrameProcessor::GetFirstFrame() const
{
	return _frames[_frameOffset];
}

const FrameProcessor::FrameInfo& FrameProcessor::GetLastFrame() const
{
	if (_frameOffset > 0)
	{
		return _frames[_frameOffset - 1];
	}
	return _frames.back();
}
