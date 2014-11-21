#include "SpriteRenderer.h"

#include <Nano/Managers/AssetManager.h>
#include <Nano/NanoEntityConfig.h>

#include "Camera.h"

void SpriteRenderer::Init() {
	auto config = static_cast<NanoEntityConfig*>(_entity->GetEntitySystem()->GetConfig());
	_sprite = AssetManager::GetInstance()->LoadSprite(_spriteName, config->renderer);

	Transform *transform = _entity->GetTransform();
	SDL_Rect spriteRect = _sprite.GetRect();
	if (approxEq(transform->size.x, 0.0f) ||
			approxEq(transform->size.y, 0.0f)) {
		transform->size.x = (float)spriteRect.w;
		transform->size.y = (float)spriteRect.h;
	}
}

void SpriteRenderer::Start() {
	_camera = _entity->GetEntitySystem()->FindEntity("Camera")->GetComponent<Camera>();
}

void SpriteRenderer::Draw() {
	Transform *transform = _entity->GetTransform();
	SDL_Rect rect = transform->GetRectWithOffset(_camera->GetOffset());
	SDL_Texture *texture = _sprite.GetTexture();
	SDL_SetTextureColorMod(texture, _sprite.color.r, _sprite.color.g, _sprite.color.b);
	auto flip = SDL_FLIP_NONE;
	if (_sprite.horizFlip) {
		flip = (SDL_RendererFlip)(flip | SDL_FLIP_HORIZONTAL);
	}
	if (_sprite.vertFlip) {
		flip = (SDL_RendererFlip)(flip | SDL_FLIP_VERTICAL);
	}
	SDL_RenderCopyEx(_sprite.GetRenderer(), texture, nullptr, &rect,
		_sprite.angle, nullptr, flip);
}

Sprite* SpriteRenderer::GetSprite() {
	return &_sprite;
}
