class Game
{
public:
	void Start()
	{
		const std::string gameTitle = "Alien Land";
		_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), gameTitle);
	
		GameLoop();
	}

private:
	void HandleInput()
	{
		sf::Event e;
		while (_window->pollEvent(e))
		{
			// handle some stuff:
			if (e.type == sf::Event::Closed)
			{
				_shouldTerminate = true;
			}
			if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
			{
				_shouldTerminate = true;
			}
		}
	}

	void Update(const std::chrono::milliseconds & dt)
	{
		// update some stuff
	}

	void Render()
	{
		_window->clear();
		// draw some stuff
		_window->display();
	}

	void GameLoop()
	{
		constexpr size_t expectedFps = 60;
		constexpr auto expectedTps = std::chrono::milliseconds(1000 / expectedFps);
		
		sf::Clock frameClock;
		while (!_shouldTerminate)
		{
			const sf::Time elapsedTime = frameClock.getElapsedTime();
			const auto elapsedMs = std::chrono::milliseconds(elapsedTime.asMilliseconds());

			HandleInput();
			Update(elapsedMs);
			Render();

			if (elapsedMs < expectedTps)
			{
				std::this_thread::sleep_for(expectedTps - elapsedMs);
			}
			frameClock.restart();
		}
	}

	std::unique_ptr<sf::RenderWindow>		_window;
	bool									_shouldTerminate = false;
};


int main()
{
	Game game;
	game.Start();
	return 0;
}