#pragma once

#include "GameLoopDelegate.h"

class GameScene;

class Game
{
public:
	Game(std::unique_ptr<GameLoopDelegate> delegate);
	~Game();

	void Start();

private:
	void GameLoop();

	std::unique_ptr<GameLoopDelegate> _delegate;
};