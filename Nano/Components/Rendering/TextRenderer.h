#pragma once

#include <Nano/Engine/Engine.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class TextRenderer : public Component {
private:
	std::string _text;
	bool _isDirty;
	SDL_Texture *_texture;
	TTF_Font *_font;
	SDL_Renderer *_renderer;

	void renderText();

public:
	TextRenderer();
	TextRenderer(std::string fontName, int fontSize);
	void Load(std::vector<std::string> const& args);
	void Init(std::string fontName, int fontSize);

	void Start();
	void Draw();

	void SetText(std::string text);
};

