#include "Render/SimpleSpriteUnitRender.h"

SimpleSpriteUnitRender::SimpleSpriteUnitRender(sf::RenderTarget & renderTarget, sf::Sprite sprite, const GameObjectTransform & transform)
	: _renderTarget(renderTarget)
	, _sprite(sprite)
	, _transform(transform)
{
}

void SimpleSpriteUnitRender::Render()
{
	_renderTarget.draw(_sprite, sf::RenderStates(_transform.GetTransform()));
}
