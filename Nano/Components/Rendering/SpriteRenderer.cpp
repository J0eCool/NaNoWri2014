#include "SpriteRenderer.h"

#include <Nano/Managers/AssetManager.h>
#include <Nano/NanoEntityConfig.h>

#include "Camera.h"

void SpriteRenderer::Load(std::vector<std::string> const& args) {
	_spriteName = args[0];
}

void SpriteRenderer::Start() {
	auto config = static_cast<NanoEntityConfig*>(_entity->GetEntitySystem()->GetConfig());
	_sprite = AssetManager::GetInstance()->LoadSprite(_spriteName, config->renderer);

	Transform *transform = _entity->GetTransform();
	SDL_Rect spriteRect = _sprite.GetRect();
	if (approxEq(transform->size.x, 0.0f) ||
			approxEq(transform->size.y, 0.0f)) {
		transform->size.x = (float)spriteRect.w;
		transform->size.y = (float)spriteRect.h;
	}

	_camera = _entity->GetEntitySystem()->FindEntity("Camera")->GetComponent<Camera>();
}

void SpriteRenderer::Draw() {
	Transform *transform = _entity->GetTransform();
	SDL_Rect rect = transform->GetRectWithOffset(_camera->GetOffset());
	SDL_Texture *texture = _sprite.GetTexture();
	SDL_SetTextureColorMod(texture, _sprite.color.r, _sprite.color.g, _sprite.color.b);
	SDL_RenderCopyEx(_sprite.GetRenderer(), texture, nullptr, &rect,
		_sprite.angle, nullptr, SDL_FLIP_NONE);
}

Sprite* SpriteRenderer::GetSprite() {
	return &_sprite;
}
