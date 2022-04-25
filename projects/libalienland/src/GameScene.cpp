#include "GameScene.h"

#include "Character.h"
#include "Enemy.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "SfmlUtils.h"
#include "Imgui/ImguiController.h"

GameScene::GameScene()
	: _bulletManager(std::make_shared<BulletManager>())
{}

GameScene::~GameScene() = default;

void GameScene::Init(std::shared_ptr<sf::RenderWindow> window, const std::filesystem::path & resourcesDirectory)
{
	Assert(window);
	_window = window;
	
	AddCharacter(resourcesDirectory, _bulletManager);
	//SetInitialPosition(_character);

	Assert(_gameObjects[0]);

	AddEnemy(resourcesDirectory);
	//SetInitialPosition(_enemy);

	InitSceneBorder();
	
	_bulletManager->Init(resourcesDirectory);

	ImguiController::Settings settings;
	{
		settings.window = window;
	}
	_imguiController = std::make_shared<ImguiController>();
	_imguiController->Init(settings);

	auto mapTexture = LoadMapTexture(resourcesDirectory);
	if (mapTexture)
	{
		_mapTexture = *std::move(mapTexture);
		_mapSprite.setTexture(_mapTexture);
		_mapSprite.setTextureRect(_sceneBorder);
	}
}

void GameScene::PreGameLoop()
{
	if (_imguiController)
	{
		_imguiController->Prepare();
	}
}

void GameScene::PostGameLoop()
{
	if (_imguiController)
	{
		_imguiController->CleanUp();
	}
}

void GameScene::PreFrame()
{
	if (_imguiController)
	{
		_imguiController->BeginFrame();
	}
}

void GameScene::ProcessInput(const sf::Event & event)
{
	if (_imguiController)
	{
		_imguiController->ProcessInput(event);
	}
	//EventLogging(event);
	ProcessSceneInput(event);
	
	for (const std::shared_ptr<GameObject> entity : _gameObjects)
	{
		entity->ProcessInput(event);
	}
}

void GameScene::Update(const sf::Time & elapsedTime)
{
	if (_imguiController)
	{
		_imguiController->BeginUpdate(elapsedTime);
	}
	
	for (std::shared_ptr<GameObject> entity : _gameObjects)
	{
		entity->Update(elapsedTime);
	}
	AddBullets();
	ProcessCollision();
	if (_shouldRemoveGameObjs)
	{
		RemoveMarkedGameObjects();
	}

	if (_imguiController)
	{
		_imguiController->EndUpdate();
	}
}

void GameScene::Render()
{
	auto window = _window.lock();
	if (!Verify2(window, "Failed to render GameScene, window must be alive."))
	{
		return;
	}
	
	window->draw(_mapSprite);

	for (const std::shared_ptr<GameObject> entity : _gameObjects)
	{
		entity->Render(*window);
	}

	if (_imguiController)
	{
		_imguiController->Render();
	}
}

void GameScene::PostFrame()
{
	if (_imguiController)
	{
		_imguiController->EndFrame();
	}
}

void GameScene::AddBullet(std::shared_ptr<GameScene> gameScene, const sf::Vector2f & curCharPos, float curCharRot, const sf::Vector2f & targetPos)
{	
	auto bullet = _bulletManager->CreateBullet(gameScene, curCharPos, curCharRot, targetPos);
	_bullets.push_back(bullet);
}

void GameScene::AddCharacter(const std::filesystem::path & resourcesDirectory, std::shared_ptr<BulletManager> bulletManager)
{
	auto character = std::make_shared<Character>();
	character->Init(resourcesDirectory, shared_from_this(), _bulletManager);
	_gameObjects.push_back(character);
	LOG_INFO() << "The main character has been created";
}

void GameScene::AddEnemy(const std::filesystem::path & resourcesDirectory)
{
	auto enemy = std::make_shared<Enemy>();
	enemy->Init(resourcesDirectory, shared_from_this());
	_gameObjects.push_back(enemy);
	LOG_INFO() << "An enemy has been created";
}

void GameScene::AddBullets()
{
	if (_bullets.empty())
	{
		return;
	}
	for (std::shared_ptr<Bullet> bullet : _bullets)
	{
		_gameObjects.push_back(bullet);
	}
	_bullets.clear();
}

void GameScene::EventLogging(const sf::Event & event)
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

void GameScene::ProcessSceneInput(const sf::Event & event)
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
void GameScene::SetInitialPosition(std::shared_ptr<T> object)
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

void GameScene::RemoveMarkedGameObjects()
{
	if (_gameObjects.empty())
	{
		return;
	}

	auto removeGameObj = std::remove_if(_gameObjects.begin(), _gameObjects.end(), [](const std::shared_ptr<GameObject> gameObject)
	{
			return gameObject->ShouldRemove();
	});

	_gameObjects.erase(removeGameObj, _gameObjects.end());
	_shouldRemoveGameObjs = false;
}

void GameScene::InitSceneBorder()
{
	auto window = _window.lock();
	auto size = Utils::VectorCast<int>(window->getSize());
	sf::Vector2i startPos(0, 0);
	_sceneBorder = sf::IntRect(startPos, size);
}

void GameScene::ProcessCollision()
{
	if (_gameObjects.empty())
	{
		return;
	}
	for (const std::shared_ptr<GameObject> entity : _gameObjects)
	{
		entity->ProcessCollision();
	}
}

std::unique_ptr<sf::Texture> GameScene::LoadMapTexture(const std::filesystem::path & resourcesDirectory)
{
	const auto mapTexturePath = (resourcesDirectory / "stone01.jpg").generic_string();
	auto texture = std::make_unique<sf::Texture>();
	if (!texture->loadFromFile(mapTexturePath))
	{
		return {};
	}
	LOG_INFO() << "Map texture has been loaded.";
	texture->setRepeated(true);
	return texture;
}
