#pragma once

#include <SDL.h>
#include <string>

#include <Nano/Engine/Engine.h>

#include <Nano/Sprite.h>

class SpriteRenderer : public Component {
private:
	Sprite _sprite;
	SDL_Renderer *_renderer;

public:
	SpriteRenderer();
	SpriteRenderer(std::string spriteName, SDL_Renderer *renderer);
	void Init(std::string spriteName, SDL_Renderer *renderer);

	void Start();
	void Draw();

	Sprite* GetSprite();
};