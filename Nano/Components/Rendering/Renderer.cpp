#include "Renderer.h"

#include <Nano/Engine/Engine.h>
#include <Nano/NanoEntityConfig.h>

Renderer::Renderer() : _color({ 0xff, 0xff, 0xff, 0xff }) {
}

void Renderer::Start() {
	auto config = static_cast<NanoEntityConfig*>(_entity->GetEntitySystem()->GetConfig());
	_renderer = config->renderer;
}

void Renderer::Draw() {
	Transform *transform = _entity->GetTransform();
	SDL_Rect rect = transform->GetRect();
	SDL_SetRenderDrawColor(_renderer, _color.r, _color.g, _color.b, _color.a);
	SDL_RenderFillRect(_renderer, &rect);
}

Renderer* Renderer::SetColor(SDL_Color color) {
	_color = color;
	return this;
}
