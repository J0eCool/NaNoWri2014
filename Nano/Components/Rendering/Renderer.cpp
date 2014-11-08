#include "Renderer.h"

#include <Nano/Engine/Engine.h>

Renderer::Renderer() : _color({ 0xff, 0xff, 0xff, 0xff }) {
}

Renderer::Renderer(SDL_Renderer *renderer) : Renderer() {
	Init(renderer);
}

void Renderer::Init(SDL_Renderer *renderer) {
	_renderer = renderer;
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
