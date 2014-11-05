#pragma once

#include <SDL.h>

#include "../Engine/Engine.h"

class Renderer : public Component {
private:
	SDL_Renderer *_renderer;
	SDL_Color _color;

public:
	Renderer();
	Renderer(SDL_Renderer *renderer);

	void Init(SDL_Renderer *renderer);
	void Draw();

	Renderer* SetColor(SDL_Color color);
};
