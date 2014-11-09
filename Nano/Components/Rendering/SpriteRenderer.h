#pragma once

#include <SDL.h>
#include <string>

#include <Nano/Engine/Engine.h>

#include <Nano/Sprite.h>

class SpriteRenderer : public Component {
private:
	Sprite _sprite;
	std::string _spriteName;

public:
	SpriteRenderer();
	SpriteRenderer(std::string spriteName);
	void Init(std::string spriteName);

	void Start();
	void Draw();

	Sprite* GetSprite();
};