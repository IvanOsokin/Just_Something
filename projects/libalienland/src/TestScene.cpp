#include "TestScene.h"

#include "Character.h"
#include "Enemy.h"
#include "BulletManager.h"
#include "Imgui/ImguiController.h"

TestScene::TestScene()
	: _bulletManager(std::make_shared<BulletManager>())
	, _character(std::make_shared<Character>())
	, _enemy(std::make_shared<Enemy>())
{}

TestScene::~TestScene() = default;

void TestScene::Init(std::shared_ptr<sf::RenderWindow> window, const std::filesystem::path & resourcesDirectory)
{
	Assert(window);
	_window = window;
	_character->Init(resourcesDirectory, _bulletManager);
	SetInitialPosition(_character);

	Assert(_character);
	_enemy->Init(resourcesDirectory, window);
	SetInitialPosition(_enemy);
	_enemy->InitBoundingBox();

	// Once the scene will be initialized by a texture it will be needed to substitute
	// values of arguments in 'position' and 'size' by the texture parameters
	sf::Vector2i position(0, 0);
	sf::Vector2i size(_window.lock()->getSize());
	sf::IntRect  sceneBorder(position, size);
	
	_bulletManager->Init(resourcesDirectory, sceneBorder, _enemy);

	ImguiController::Settings settings;
	{
		settings.window = window;
	}
	_imguiController = std::make_shared<ImguiController>();
	_imguiController->Init(settings);
}

void TestScene::PreGameLoop()
{
	if (_imguiController)
	{
		_imguiController->Prepare();
	}
}

void TestScene::PostGameLoop()
{
	if (_imguiController)
	{
		_imguiController->CleanUp();
	}
}

void TestScene::PreFrame()
{
	if (_imguiController)
	{
		_imguiController->BeginFrame();
	}
}

void TestScene::ProcessInput(const sf::Event & event)
{
	if (_imguiController)
	{
		_imguiController->ProcessInput(event);
	}
	EventLogging(event);
	ProcessSceneInput(event);
	_character->ProcessInput(event);
	if (_enemy)
	{
		_enemy->ProcessInput(event);
	}
}

void TestScene::Update(const sf::Time & elapsedTime)
{
	if (_imguiController)
	{
		_imguiController->BeginUpdate(elapsedTime);
	}
	_character->Update(elapsedTime);

	if (_enemy)
	{
		//_enemy->MoveTo(_character->GetPosition());
		_enemy->Update(elapsedTime);
	}
	
	_bulletManager->Update(elapsedTime);

	if (_enemy)
	{
		RemoveDeadEnemy();
	}

	if (_imguiController)
	{
		_imguiController->EndUpdate();
	}
}

void TestScene::Render()
{
	auto window = _window.lock();
	if (!Verify2(window, "Failed to render TestScene, window must be alive."))
	{
		return;
	}
	
	_character->Render(*window);
	if (_enemy)
	{
		_enemy->Render(*window);
	}
	_bulletManager->Render(*window);

	if (_imguiController)
	{
		_imguiController->Render();
	}
}

void TestScene::PostFrame()
{
	if (_imguiController)
	{
		_imguiController->EndFrame();
	}
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
void TestScene::SetInitialPosition(std::shared_ptr<T> object)
{
	if (!_window.lock())
	{
		LOG_ERROR() << "The window was lost.";
		object->GetSprite().setPosition( 0.0f, 0.0f );
		return;
	}
	
	const auto windowSize = _window.lock()->getSize();
	object->SetPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f));
	object->GetSprite().setPosition(object->GetPosition());
}

void TestScene::RemoveDeadEnemy()
{
	if (_enemy->IsDead())
	{
		_enemy.reset();
	}
}