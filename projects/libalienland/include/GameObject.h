#pragma once

class GameObjectRender
{
public:
	virtual ~GameObjectRender() = default;
	virtual void Render() = 0;
};

class GameObject
{
public:
	virtual ~GameObject() = default;

	void SetRender(std::unique_ptr<GameObjectRender> render);

	virtual void ProcessInput(const sf::Event& /*event*/) {};
	virtual void Update(const sf::Time& /*elapsedTime*/) {}
	virtual void ProcessCollision() {};

	void Render();

	enum class GameObjectType
	{
		character,
		enemy,
		bullet
	};

	GameObjectType GetGameObjectType() { return _gameObjectType; }
	void SetGameObjectId(GameObjectType gameObjectId) { _gameObjectType = gameObjectId; }
	bool ShouldRemove() const { return _shouldRemove; }
	void SetShouldRemoveState(bool shouldRemove) { _shouldRemove = shouldRemove; }

private:
	sf::Texture		_texture;
	GameObjectType	_gameObjectType;
	bool			_shouldRemove = false;
	std::unique_ptr<GameObjectRender>		_render;
};