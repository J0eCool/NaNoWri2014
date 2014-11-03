#pragma once

#include <SDL.h>

#include "../Component.h"

class Renderer : public Component {
private:
	SDL_Renderer *_renderer;
	SDL_Color _color;

public:
	Renderer();

	void Init(SDL_Renderer *renderer);
	void Draw();

	void SetColor(SDL_Color color);
};
