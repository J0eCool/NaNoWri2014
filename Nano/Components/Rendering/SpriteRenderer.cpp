#include "SpriteRenderer.h"

#include <Nano/Managers/AssetManager.h>

SpriteRenderer::SpriteRenderer() { }
SpriteRenderer::SpriteRenderer(std::string spriteName, SDL_Renderer *renderer) {
	Init(spriteName, renderer);
}
void SpriteRenderer::Init(std::string spriteName, SDL_Renderer *renderer) {
	_sprite = AssetManager::GetInstance()->LoadSprite(spriteName, renderer);
	_renderer = renderer;
}

void SpriteRenderer::Start() {
	Transform *transform = _entity->GetTransform();
	SDL_Rect spriteRect = _sprite.GetRect();
	if (approxEq(transform->size.x, 0.0f) ||
			approxEq(transform->size.y, 0.0f)) {
		transform->size.x = (float)spriteRect.w;
		transform->size.y = (float)spriteRect.h;
	}
}

void SpriteRenderer::Draw() {
	Transform *transform = _entity->GetTransform();
	SDL_Rect rect = transform->GetRect();
	SDL_Texture *texture = _sprite.GetTexture();
	SDL_SetTextureColorMod(texture, _sprite.color.r, _sprite.color.g, _sprite.color.b);
	SDL_RenderCopyEx(_renderer, texture, nullptr, &rect,
		_sprite.angle, nullptr, SDL_FLIP_NONE);
}

Sprite* SpriteRenderer::GetSprite() {
	return &_sprite;
}
