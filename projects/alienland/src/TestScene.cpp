#include "TestScene.h"

#include "Character.h"
#include "Enemy.h"

TestScene::TestScene()
	: _character(std::make_unique<Character>())
	, _enemy(std::make_unique<Enemy>())
{}

TestScene::~TestScene() = default;

void TestScene::Init(std::shared_ptr<sf::RenderWindow> window)
{
	_window = window;
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
	if (TerminateIfEmptyWindow())
	{
		return;
	}

	auto sharedWindow = _window.lock();
	_character->Render(*sharedWindow);
	_enemy->Render(*sharedWindow);
}

void TestScene::EventLogging(const sf::Event & event)
{
	std::string eventCodeStr;

	switch (event.type)
	{
	case sf::Event::KeyPressed: 
		eventCodeStr = std::to_string(event.key.code);
		LOG_INFO(eventCodeStr + "\t- code of pressed button");
		break;
	case sf::Event::MouseButtonPressed:
		eventCodeStr = std::to_string(event.mouseButton.button);
		LOG_INFO(eventCodeStr + "\t- code of pressed mouse button");
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

bool TestScene::TerminateIfEmptyWindow()
{
	if (_window.lock())
	{
		return false;
	}

	sf::err() << "Failed to process test scene, render window must be set." << std::endl;
	_shouldTerminate = true;
	return true;
}

