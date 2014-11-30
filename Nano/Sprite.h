#pragma once

#include <SDL.h>
#include <string>

class AssetManager;

class Sprite {
private:
	SDL_Texture *_texture;
	SDL_Renderer *_renderer;
	int _width;
	int _height;

public:
	Sprite();

	SDL_Color color;
	float angle = 0.0f;
	bool horizFlip = false;
	bool vertFlip = false;

	SDL_Texture* GetTexture() const;
	SDL_Renderer* GetRenderer() const;
	SDL_Rect GetRect() const;

	void DrawAt(SDL_Rect const& rect) const;

	friend AssetManager;
};