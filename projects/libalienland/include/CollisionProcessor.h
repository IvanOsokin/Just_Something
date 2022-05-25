#pragma once

class GameObject;

class CollisionProcessor
{
public:
	CollisionProcessor(std::vector<std::shared_ptr<GameObject>> & gameObjects);
	~CollisionProcessor();

	void ProcessCollision();

private:
	std::vector<std::shared_ptr<GameObject>> & _gameObjects;
};