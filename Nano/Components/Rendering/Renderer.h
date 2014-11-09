#pragma once

#include <SDL.h>

#include <Nano/Engine/Engine.h>

class Renderer : public Component {
private:
	SDL_Renderer *_renderer;
	SDL_Color _color;

public:
	Renderer();

	void Start();
	void Draw();

	Renderer* SetColor(SDL_Color color);
};
