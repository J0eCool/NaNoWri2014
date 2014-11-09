#include "TextRenderer.h"

#include <Nano/Managers/AssetManager.h>

TextRenderer::TextRenderer() :
		_text(""), _isDirty(true), _texture(nullptr) {
}
TextRenderer::TextRenderer(TTF_Font *font, SDL_Renderer *renderer) : TextRenderer() {
	Init(font, renderer);
}

void TextRenderer::Init(TTF_Font *font, SDL_Renderer *renderer) {
	_font = font;
	_renderer = renderer;
}

void TextRenderer::renderText() {
	SDL_DestroyTexture(_texture);
	SDL_Surface *surface = TTF_RenderText_Solid(_font, _text.c_str(), { 0, 0, 0 });
	Transform *transform = _entity->GetTransform();
	transform->size.x = (float)surface->w;
	transform->size.y = (float)surface->h;
	_texture = SDL_CreateTextureFromSurface(_renderer, surface);
	SDL_FreeSurface(surface);
	_isDirty = false;
}

void TextRenderer::Draw() {
	Transform *transform = _entity->GetTransform();

	if (_isDirty) {
		renderText();
	}
	
	SDL_Rect rect(transform->GetRect());
	SDL_RenderCopy(_renderer, _texture, nullptr, &rect);
}

void TextRenderer::SetText(std::string text) {
	if (_text != text) {
		_isDirty = true;
		_text = text;
	}
}
