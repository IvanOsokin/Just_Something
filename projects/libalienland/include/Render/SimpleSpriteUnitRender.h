#pragma once
#include "GameObject.h"

class SimpleSpriteUnitRender : public GameObjectRender
{
public:
	SimpleSpriteUnitRender(sf::RenderTarget & renderTarget, sf::Sprite sprite, const GameObjectTransform & transform);

	void Render() override;

private:
	sf::RenderTarget &				_renderTarget;
	sf::Sprite						_sprite;
	const GameObjectTransform &		_transform;
};
