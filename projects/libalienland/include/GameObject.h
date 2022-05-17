#pragma once
#include "GameObjectTransform.h"

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
	virtual void Update(float /*elapsedTime*/) {}
	virtual void ProcessCollision() {};

	void Render();

	auto & Transform() { return _transform; }
	const auto & Transform() const { return _transform; }

	bool ShouldRemove() const { return _shouldRemove; }
	void SetShouldRemoveState(bool shouldRemove) { _shouldRemove = shouldRemove; }

private:
	bool			_shouldRemove = false;
	GameObjectTransform						_transform;
	std::unique_ptr<GameObjectRender>		_render;
};