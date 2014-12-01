#pragma once

#include <SDL.h>

#include <Nano/Engine/Engine.h>

#include "Bullet.h"

class PlayerController : public Component {
private:
	float _speed;
	float _jumpHeight;
	Vec2 _shotOffset;

	int _maxHealth = 20;
	int _maxMana = 8;
	int _health;
	int _mana;

	bool _isHoldingJump = false;
	int _facingDir = 1;

	Bullet::Container _normalShots;
	Bullet::Container _specialShots;

public:
	PlayerController();
	//$$_speed:Float|_jumpHeight:Float|_shotOffset:Vec2
	void LoadArg(String const& key, String const& val) override;
	void Start() override;
	void Update(float dt) override;
	void HandleMessage(String const& message, void* data) override;
};
