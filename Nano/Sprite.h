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

	SDL_Texture* GetTexture() const;
	SDL_Renderer* GetRenderer() const;
	SDL_Rect GetRect() const;

	friend AssetManager;
};