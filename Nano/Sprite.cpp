#include "Sprite.h"

#include <Nano/Managers/AssetManager.h>

Sprite::Sprite() : angle(0.0f), color({ 0xff, 0xff, 0xff, 0xff }) {
}

SDL_Renderer* Sprite::GetRenderer() const {
	return _renderer;
}

SDL_Texture* Sprite::GetTexture() const {
	return _texture;
}

SDL_Rect Sprite::GetRect() const {
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = _width;
	rect.h = _height;
	return rect;
}

