#pragma once

class GameLoopDelegate
{
public:
	virtual ~GameLoopDelegate() = default;

	virtual int RequestedFps() const = 0;

	virtual void PreGameLoop() = 0;
	virtual void PostGameLoop() = 0;

	virtual void PreFrame() = 0;
	virtual void PostFrame() = 0;

	virtual void Update(float deltaTime) = 0;
	virtual void Input() = 0;
	virtual void Render() = 0;

	virtual bool ShouldTerminate() const = 0;
};