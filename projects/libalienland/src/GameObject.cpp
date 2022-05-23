#include "GameObject.h"

void GameObject::SetRender(std::unique_ptr<GameObjectRender> render)
{
	_render = std::move(render);
}

void GameObject::Render()
{
	if (_render)
	{
		_render->Render();
	}
}
