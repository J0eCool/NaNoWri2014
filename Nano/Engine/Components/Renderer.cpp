#include "Renderer.h"

#include "../Entity.h"
#include "Transform.h"

Renderer::Renderer() : _color({ 0xff, 0xff, 0xff, 0xff }) {
}

void Renderer::Init(SDL_Renderer *renderer) {
	_renderer = renderer;
}

void Renderer::Draw() {
	Transform *transform = _entity->GetComponent<Transform>();
	SDL_Rect rect = transform->GetRect();
	SDL_SetRenderDrawColor(_renderer, _color.r, _color.g, _color.b, _color.a);
	SDL_RenderFillRect(_renderer, &rect);
}

void Renderer::SetColor(SDL_Color color) {
	_color = color;
}
