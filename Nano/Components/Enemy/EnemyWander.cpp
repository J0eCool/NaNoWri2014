#include "EnemyWander.h"

#include <Nano/Components/Components.h>

EnemyWander::EnemyWander() : _dir(-1) {
}

void EnemyWander::Update(float dt) {
	auto rigidbody = GetComponent<Rigidbody>();
	auto renderer = GetComponent<SpriteRenderer>();
	if (rigidbody->IsColliding(CD_Down)) {
		auto colDir = _dir < 0 ? CD_DownLeftSide : CD_DownRightSide;
		auto notColDir = _dir < 0 ? CD_Left : CD_Right;

		if (!rigidbody->IsColliding(colDir) || rigidbody->IsColliding(notColDir)) {
			_dir = -_dir;
		}
	}

	rigidbody->vel.x = _dir * _speed;
	renderer->GetSprite()->horizFlip = _dir > 0;
}
