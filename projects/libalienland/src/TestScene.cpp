#include "TestScene.h"

#include "Character.h"
#include "Enemy.h"
#include "BulletManager.h"

TestScene::TestScene()
	: _character(std::make_unique<Character>())
	, _enemy(std::make_unique<Enemy>())
	, _bulletManager(std::make_shared<BulletManager>())
{}

TestScene::~TestScene() = default;

void TestScene::Init(std::shared_ptr<sf::RenderWindow> window, const std::filesystem::path & resourcesDirectory)
{
	Assert(window);
	_window = window;
	_character->Init(resourcesDirectory);
	SetInitialPosition(_character);

	Assert(_character);
	_enemy->Init(resourcesDirectory, window);
	SetInitialPosition(_enemy);

	// Once the scene will be initialized by a texture it will be needed to substitute
	// values of arguments in 'position' and 'size' by the texture parameters
	sf::Vector2i position(0, 0);
	sf::Vector2i size(_window.lock()->getSize());

	sf::IntRect sceneBorder(position, size);
	_bulletManager->Init(sceneBorder, resourcesDirectory);
}

void TestScene::ProcessInput(const sf::Event & event)
{
	EventLogging(event);
	ProcessSceneInput(event);
	_character->ProcessInput(event);
	_enemy->ProcessInput(event);
}

void TestScene::Update(const sf::Time & elapsedTime)
{
	_character->Update(elapsedTime);
	_enemy->MoveTo(_character->GetPosition());
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
		LOG_INFO() << std::setw(3) << event.key.code << " - code of pressed button";
		break;
	case sf::Event::MouseButtonPressed:
		LOG_INFO() << event.mouseButton.button << " - code of pressed mouse button";
		break;
	default:
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

template <typename T>
void TestScene::SetInitialPosition(std::unique_ptr<T> & object)
{
	if (!_window.lock())
	{
		LOG_ERROR() << "The window was lost.";
		object->GetSprite().setPosition( 0.0f, 0.0f );
		return;
	}

	auto textureSize = object->GetSprite().getTexture()->getSize();
	object->GetSprite().setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
	
	auto windowSize = _window.lock()->getSize();
	object->SetPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f));
	object->GetSprite().setPosition(object->GetPosition());
}