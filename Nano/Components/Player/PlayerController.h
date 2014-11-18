#pragma once

#include <SDL.h>

#include <Nano/Engine/Engine.h>

class PlayerController : public Component {
private:
	float _speed;
	float _jumpHeight;
	Vec2 _shotOffset;

	bool _isHoldingJump = false;
	int _facingDir = 1;

	const float kGravity = 2500.0f;

public:
	PlayerController();
	//$$_speed:Float|_jumpHeight:Float|_shotOffset:Vec2
	void LoadArg(String const& key, String const& val) override;

	void Update(float dt) override;
};

