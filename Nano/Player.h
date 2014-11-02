#pragma once

#include <SDL.h>

#include "Vec2.h"

class Player {
private:
	Vec2 _size;
	Vec2 _pos;
	Vec2 _vel;
	bool onGround = false;

	float _speed = 350.0f;
	const float kGravity = 1000.0f;

public:
	Player(Vec2 size, Vec2 pos);

	void Update(float dt);
	void Draw(SDL_Renderer *renderer) const;
};

