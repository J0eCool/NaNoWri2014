#include "TextRenderer.h"

#include <Nano/Managers/AssetManager.h>
#include <Nano/NanoEntityConfig.h>

TextRenderer::TextRenderer() :
		_text(""), _isDirty(true), _texture(nullptr) {
}
TextRenderer::TextRenderer(std::string fontName, int fontSize) : TextRenderer() {
	Init(fontName, fontSize);
}

void TextRenderer::Load(std::vector<std::string> const& args) {
	std::string fontName = args[0];
	int fontSize = atoi(args[1].c_str());
	Init(fontName, fontSize);
}

void TextRenderer::Init(std::string fontName, int fontSize) {
	_font = AssetManager::GetInstance()->LoadFont(fontName, fontSize);
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

void TextRenderer::Start() {
	auto config = static_cast<NanoEntityConfig*>(_entity->GetEntitySystem()->GetConfig());
	_renderer = config->renderer;
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
