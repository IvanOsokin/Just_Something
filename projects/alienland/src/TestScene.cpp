#include "TestScene.h"

#include "Character.h"
#include "Enemy.h"

TestScene::TestScene()
	: _character(std::make_unique<Character>())
	, _enemy(std::make_unique<Enemy>())
{}

TestScene::~TestScene() = default;

void TestScene::Init(sf::RenderWindow & window)
{
	_window = &window;
}

void TestScene::ProcessInput(const sf::Event& event)
{
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

	_character->Render(*_window);
	_enemy->Render(*_window);
}

void TestScene::ProcessSceneInput(const sf::Event& event)
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
	if (_window)
	{
		return false;
	}

	sf::err() << "Failed to process test scene, render window must be set." << std::endl;
	_shouldTerminate = true;
	return true;
}
