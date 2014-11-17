#pragma once

#include <Nano/Engine/Engine.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class TextRenderer : public Component {
private:
	std::string _fontName;
	int _fontSize;
	std::string _text;
	bool _isDirty;
	SDL_Texture *_texture;
	TTF_Font *_font;
	SDL_Renderer *_renderer;

	void renderText();

public:
	TextRenderer();
	//$$_fontName:String|_fontSize:Int
	void LoadArg(std::string const& key, std::string const& val) override;

	void Start() override;
	void Draw() override;

	void SetText(std::string text);
};

