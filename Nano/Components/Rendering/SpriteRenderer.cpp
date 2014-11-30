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
	_sprite.DrawAt(rect);
}

Sprite* SpriteRenderer::GetSprite() {
	return &_sprite;
}
