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

void Sprite::DrawAt(SDL_Rect const& rect) const {
	SDL_SetTextureColorMod(_texture, color.r, color.g, color.b);
	auto flip = SDL_FLIP_NONE;
	if (horizFlip) {
		flip = (SDL_RendererFlip)(flip | SDL_FLIP_HORIZONTAL);
	}
	if (vertFlip) {
		flip = (SDL_RendererFlip)(flip | SDL_FLIP_VERTICAL);
	}
	SDL_RenderCopyEx(_renderer, _texture, nullptr, &rect,
		angle, nullptr, flip);
}
