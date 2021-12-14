#include "Imgui/Impl/FrameProcessor.h"

void FrameProcessor::ResetHistory(size_t historyLength)
{
	_frames.resize(historyLength);
	_frameStart = 0;
	_frameEnd = 0;
	_cache = {};
}

void FrameProcessor::FrameStart()
{
	_incompleteFrame.start = ClockType::now();
}

void FrameProcessor::FrameEnd()
{
	FrameInfo frame;
	frame.start = _incompleteFrame.start;
	frame.elapsedTime = ClockType::now() - _incompleteFrame.start;

	AddFrame(std::move(frame));
}

void FrameProcessor::RecalculateFramesPerSecond()
{
	bool noFrameProcessed = true;
	TimePoint firstFrameStart;
	TimePoint lastFrameStart;
	size_t frames = 0;
	FrameByPassCallback callback = [&](const FrameInfo & frame)
	{
		if (noFrameProcessed)
		{
			firstFrameStart = frame.start;
			noFrameProcessed = false;
		}
		lastFrameStart = frame.start;
		frames += 1;
		return FrameByPassStatus::Continue;
	};
	ForeachFrame(callback);

	const Duration allFramesDuration = lastFrameStart - firstFrameStart;
	if (allFramesDuration <= Duration::zero())
	{
		_cache.fps = 0.0f;
		return;
	}

	using PrecisionType = std::chrono::microseconds;
	const auto duration = std::chrono::duration_cast<PrecisionType>(allFramesDuration).count();
	const double seconds = duration / static_cast<double>(PrecisionType::period::den);

	_cache.fps = static_cast<float>(frames / seconds);
}

void FrameProcessor::RecalculateTimePerFrame()
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

	if (frames == 0)
	{
		_cache.tps = std::chrono::microseconds::zero();
		return;
	}

	const auto mcs = static_cast<uint64_t>(seconds * 1'000'000);
	_cache.tps = std::chrono::microseconds(mcs) / frames;
}

float FrameProcessor::GetFramesPerSecond() const
{
	return _cache.fps;
}

std::chrono::microseconds FrameProcessor::GetTimePerFrame() const
{
	return _cache.tps;
}

void FrameProcessor::AddFrame(FrameInfo frame)
{
	_frames[_frameEnd] = std::move(frame);

	_frameEnd = (_frameEnd + 1) % _frames.size();
	if (_frameStart == _frameEnd)
	{
		_frameStart += 1;
	}
}

void FrameProcessor::ForeachFrame(const FrameByPassCallback& callback) const
{
	auto ProcessIteration = [&](size_t frameOffset)
	{
		const auto & frame = _frames[frameOffset];
		const auto status = callback(frame);
		return status;
	};

	auto byPassSatus = FrameByPassStatus::Continue;
	size_t frameEnd = _frameStart < _frameEnd ? _frameEnd : _frames.size();
	for (size_t frameOffset = _frameStart; 
		frameOffset < frameEnd && byPassSatus != FrameByPassStatus::Stop; 
		++frameOffset)
	{
		byPassSatus = ProcessIteration(frameOffset);
	}

	frameEnd = _frameStart > _frameEnd ? _frameEnd : 0;
	for (size_t frameOffset = 0; 
		frameOffset < frameEnd && byPassSatus != FrameByPassStatus::Stop; 
		++frameOffset)
	{
		byPassSatus = ProcessIteration(frameOffset);
	}
}
