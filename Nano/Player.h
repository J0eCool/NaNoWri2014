#pragma once

#include <SDL.h>

#include "Util/Vec2.h"

class Player {
private:
	Vec2 _size;
	Vec2 _pos;
	Vec2 _vel;
	bool onGround = false;

	float _speed;
	float _jumpHeight;
	float _groundHeight;
	const float kGravity = 2500.0f;

public:
	Player(Vec2 size, Vec2 pos);

	void Update(float dt);
	void Draw(SDL_Renderer *renderer) const;

	Vec2 GetPos() { return _pos; }
};

