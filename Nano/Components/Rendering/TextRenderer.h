#pragma once

#include <Nano/Engine/Engine.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class TextRenderer : public Component {
private:
	String _fontName;
	int _fontSize;
	String _text;
	bool _isDirty;
	SDL_Texture *_texture;
	TTF_Font *_font;
	SDL_Renderer *_renderer;

	void renderText();

public:
	TextRenderer();
	//$$_fontName:String|_fontSize:Int
	void LoadArg(String const& key, String const& val) override;

	void Start() override;
	void Draw() override;

	void SetText(String text);
};

