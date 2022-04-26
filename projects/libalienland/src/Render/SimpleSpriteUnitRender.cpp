#include "Render/SimpleSpriteUnitRender.h"

SimpleSpriteUnitRender::SimpleSpriteUnitRender(sf::RenderTarget & renderTarget, sf::Sprite sprite, const GameObjectTransform & transform)
	: _renderTarget(renderTarget)
	, _sprite(sprite)
	, _transform(transform)
{
}

void SimpleSpriteUnitRender::SetBoundsToRender(sf::FloatRect localBounds)
{
	_localBounds = localBounds;
}

void SimpleSpriteUnitRender::Render()
{
	_renderTarget.draw(_sprite, sf::RenderStates(_transform.GetTransform()));

	if (_localBounds)
	{
		sf::RectangleShape bboxVisualizer;
		bboxVisualizer.setOutlineColor(sf::Color::Yellow);
		bboxVisualizer.setFillColor(sf::Color::Transparent);
		bboxVisualizer.setOutlineThickness(2.0f);
		
		bboxVisualizer.setOrigin(_localBounds->width / 2/* + 14*/, _localBounds->height / 2/* - 3*/);
		bboxVisualizer.setSize(sf::Vector2f(_localBounds->width, _localBounds->height));
		bboxVisualizer.setScale(_transform.GetScale());
		bboxVisualizer.setPosition(_transform.GetPosition());
		bboxVisualizer.setRotation(_transform.GetRotation());
	
		_renderTarget.draw(bboxVisualizer);
	}
}
