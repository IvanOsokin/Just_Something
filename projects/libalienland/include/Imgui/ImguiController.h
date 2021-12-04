#pragma once

class ImguiController
{
public:
	struct Settings
	{
		std::shared_ptr<sf::RenderWindow>		window;
	};
	void Init(const Settings & settings);

	void Prepare();
	void CleanUp();

	void ProcessInput(const sf::Event & event);
	void BeginUpdate(sf::Time elapsedTime);
	void EndUpdate();
	void Render();

private:
	std::weak_ptr<sf::RenderWindow>			_window;
};
