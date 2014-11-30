#pragma once

#include <Nano/Engine/Engine.h>

class EnemyJumping : public Component {
private:
	float _jumpHeight;
	float _speed;
	float _jumpDelay;
	int _dir;

	float _jumpTimer;

public:
	EnemyJumping();
	//$$_jumpHeight:Float|_speed:Float|_jumpDelay:Float|_dir:Int
	void LoadArg(String const& key, String const& val) override;
	void Update(float dt) override;
};
