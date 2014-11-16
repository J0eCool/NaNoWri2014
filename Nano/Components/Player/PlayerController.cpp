#include "PlayerController.h"

#include <Nano/Managers/InputManager.h>
#include <Nano/Constants.h>

#include <Nano/Components/Components.h>

PlayerController::PlayerController() : _speed(350.0f), _jumpHeight(180.0f) {
}

void PlayerController::Update(float dt) {
	static bool gravityDown = true;
	InputManager *input = InputManager::GetInstance();
	Transform *transform = _entity->GetTransform();
	Rigidbody *rigidbody = GetComponent<Rigidbody>();
	Vec2 vel = rigidbody->vel;
	vel.x = _speed * input->GetAxis(IA_Horizontal);

	auto collided = GetComponent<Rigidbody>()->GetCollisionDirs();
	float gDir = 1.0f;
	if (collided & CD_Up) {
		vel.y = 0.0f;
	}
	if (collided & CD_Down) {
		vel.y = 0.0f;
		if (input->IsDown(IT_Jump)) {
			vel.y = -gDir * sqrt(2.0f * _jumpHeight * kGravity);
			_isHoldingJump = true;
		}
	}
	else {
		vel.y += gDir * kGravity * dt;
	}
	if (_isHoldingJump && !input->IsHeld(IT_Jump)) {
		_isHoldingJump = false;
		if (vel.y * gDir < 0.0f) {
			vel.y *= 0.35f;
		}
	}
	rigidbody->vel = vel;

	Entity* text = _entity->GetEntitySystem()->FindEntity("PlayerPosText");
	if (text) {
		text->GetComponent<TextRenderer>()->SetText(transform->pos.ToString());
	}
}
