#pragma once

#include <SDL.h>

#include <Nano/Engine/Engine.h>

class Player : public Component {
private:
	Vec2 _vel;
	bool _onGround = false;
	bool _isHoldingJump = false;

	float _speed;
	float _jumpHeight;
	float _groundHeight;
	const float kGravity = 2500.0f;

public:
	Player();

	void Update(float dt);
};

