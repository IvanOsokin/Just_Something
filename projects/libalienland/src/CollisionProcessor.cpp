#pragma once

#include "CollisionProcessor.h"
#include "GameObject.h"

CollisionProcessor::CollisionProcessor(std::vector<std::shared_ptr<GameObject>> & gameObjects)
	: _gameObjects(gameObjects)
{}

CollisionProcessor::~CollisionProcessor() = default;

void CollisionProcessor::ProcessCollision()
{
	for (auto entity : _gameObjects)
	{
		entity->ProcessCollision();
	}
}