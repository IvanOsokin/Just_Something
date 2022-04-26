#include "GameScene.h"

#include "Character.h"
#include "Enemy.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "SfmlUtils.h"
#include "Imgui/ImguiController.h"
#include "Render/SimpleSpriteUnitRender.h"

GameScene::GameScene() = default;
GameScene::~GameScene() = default;

void GameScene::Init(std::shared_ptr<sf::RenderWindow> window, const std::filesystem::path & resourcesDirectory)
{
	if (!Verify2(window, "Window is not supplied."))
	{
		return;
	}

	_window = window;
	_bulletManager = std::make_shared<BulletManager>(*window);
	
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

	std::vector<std::shared_ptr<GameObject>> gameObjects = _gameObjects;
	for (auto & gameObject : gameObjects)
	{
		gameObject->ProcessInput(event);
	}
}

void GameScene::Update(const sf::Time & elapsedTime)
{
	if (_imguiController)
	{
		_imguiController->BeginUpdate(elapsedTime);
	}
	
	for (auto & gameObject : _gameObjects)
	{
		gameObject->Update(elapsedTime);
	}

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

	for (const auto & gameObject : _gameObjects)
	{
		gameObject->Render();
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
	_gameObjects.push_back(bullet);
}

void GameScene::AddCharacter(const std::filesystem::path & resourcesDirectory, std::shared_ptr<BulletManager> bulletManager)
{
	auto character = std::make_shared<Character>();
	character->Init(resourcesDirectory, shared_from_this(), _bulletManager);

	auto window = _window.lock();

	auto sprite = sf::Sprite(character->GetTexture());
	sprite.setOrigin(68.0f, 92.0f);

	auto render = std::make_unique<SimpleSpriteUnitRender>(*window, sprite, character->Transform());
	
	character->SetRender(std::move(render));
	_gameObjects.push_back(character);
	LOG_INFO() << "The main character has been created";
}

void GameScene::AddEnemy(const std::filesystem::path & resourcesDirectory)
{
	auto enemy = std::make_shared<Enemy>();

	auto boundingBox = sf::FloatRect(0, 0, 64.0f, 24.0f);
	enemy->Init(resourcesDirectory, boundingBox);

	auto sprite = sf::Sprite(enemy->GetTexture());
	sprite.setOrigin(65.0f, 83.0f);

	auto window = _window.lock();
	auto render = std::make_unique<SimpleSpriteUnitRender>(*window, sprite, enemy->Transform());
	render->SetBoundsToRender(boundingBox);
	
	enemy->SetRender(std::move(render));
	_gameObjects.push_back(enemy);
	LOG_INFO() << "An enemy has been created";
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
