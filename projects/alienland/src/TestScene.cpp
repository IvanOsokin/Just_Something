#include "TestScene.h"

#include "Character.h"
#include "Enemy.h"

TestScene::TestScene()
	: _character(std::make_unique<Character>())
	, _enemy(std::make_unique<Enemy>())
{}

TestScene::~TestScene() = default;

void TestScene::Init(std::shared_ptr<sf::RenderWindow> window, const std::filesystem::path & resourcesDirectory)
{
	Assert(window);
	_window = window;
	_character->Init(resourcesDirectory, window);
}

void TestScene::ProcessInput(const sf::Event & event)
{
	EventLogging(event);
	ProcessSceneInput(event);
	_character->ProcessInput(event);
}

void TestScene::Update(sf::Time elapsedTime)
{
	_character->Update(elapsedTime);
	_enemy->Update(elapsedTime);
}

void TestScene::Render()
{
	auto window = _window.lock();
	if (!Verify2(window, "Failed to render TestScene, window must be alive."))
	{
		return;
	}
	
	_character->Render(*window);
	_enemy->Render(*window);
}

void TestScene::EventLogging(const sf::Event & event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed: 
		LOG_INFO() << event.key.code << " - code of pressed button";
		break;
	case sf::Event::MouseButtonPressed:
		LOG_INFO() << event.mouseButton.button << "\t- code of pressed mouse button";
		break;
	}
}

void TestScene::ProcessSceneInput(const sf::Event & event)
{
	if (event.type == sf::Event::Closed)
	{
		_shouldTerminate = true;
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		_shouldTerminate = true;
	}
}