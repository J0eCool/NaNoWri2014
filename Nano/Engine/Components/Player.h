#pragma once

#include <SDL.h>

#include "../../Util/Vec2.h"
#include "../Component.h"

class Player : public Component {
private:
	Vec2 _vel;
	bool onGround = false;

	float _speed;
	float _jumpHeight;
	float _groundHeight;
	const float kGravity = 2500.0f;

public:
	Player();

	void Update(float dt);
};

