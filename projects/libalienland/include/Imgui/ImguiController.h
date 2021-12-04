#pragma once

class ImguiWidgetBase;

class ImguiController
{
public:
	ImguiController();
	~ImguiController();

	struct Settings
	{
		std::shared_ptr<sf::RenderWindow>		window;
	};
	void Init(const Settings & settings);

	void Prepare();
	void CleanUp();

	void BeginFrame();
	void ProcessInput(const sf::Event & event);
	void BeginUpdate(sf::Time elapsedTime);
	void EndUpdate();
	void Render();
	void EndFrame();

private:
	using ImguiWidgetPtr = std::unique_ptr<ImguiWidgetBase>;

	std::weak_ptr<sf::RenderWindow>				_window;
	bool										_open = false;
	std::vector<ImguiWidgetPtr>					_widgets;
};
