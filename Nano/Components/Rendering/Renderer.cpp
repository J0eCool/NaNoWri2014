#include "Renderer.h"

#include <Nano/Engine/Engine.h>
#include <Nano/NanoEntityConfig.h>

#include "Camera.h"

Renderer::Renderer() : _color({ 0xff, 0xff, 0xff, 0xff }) {
}

void Renderer::Load(std::vector<std::string> const& args) {
	int r = ParseInt(args[0]);
	int g = ParseInt(args[1]);
	int b = ParseInt(args[2]);
	int a = ParseInt(args[3]);

	_color = { r, g, b, a, };
}


void Renderer::Start() {
	auto config = static_cast<NanoEntityConfig*>(_entity->GetEntitySystem()->GetConfig());
	_renderer = config->renderer;
	_camera = _entity->GetEntitySystem()->FindEntity("Camera")->GetComponent<Camera>();
}

void Renderer::Draw() {
	Transform *transform = _entity->GetTransform();
	SDL_Rect rect = transform->GetRectWithOffset(_camera->GetOffset());
	SDL_SetRenderDrawColor(_renderer, _color.r, _color.g, _color.b, _color.a);
	SDL_RenderFillRect(_renderer, &rect);
}

Renderer* Renderer::SetColor(SDL_Color color) {
	_color = color;
	return this;
}
