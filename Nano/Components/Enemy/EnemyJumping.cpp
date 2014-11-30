#include "EnemyJumping.h"

#include <Nano/Components/Components.h>

EnemyJumping::EnemyJumping() : _jumpTimer(0.0f), _dir(-1) {
}

void EnemyJumping::Update(float dt) {
	auto rigidbody = GetComponent<Rigidbody>();
	auto renderer = GetComponent<SpriteRenderer>();
	
	auto colDir = _dir < 0 ? CD_Left : CD_Right;
	if (rigidbody->IsColliding(colDir)) {
		rigidbody->vel.x = -rigidbody->vel.x;
		_dir = -_dir;
	}

	if (rigidbody->IsColliding(CD_Down)) {
		_jumpTimer += dt;
		rigidbody->vel.x = 0.0f;
		if (_jumpTimer >= _jumpDelay) {
			_jumpTimer = 0.0f;
			rigidbody->vel = { _dir * _speed, -sqrt(2.0f * _jumpHeight * Rigidbody::kGravity) };
		}
	}

	renderer->GetSprite()->horizFlip = _dir > 0;
}

