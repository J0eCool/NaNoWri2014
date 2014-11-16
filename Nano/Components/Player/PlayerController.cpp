#include "PlayerController.h"

#include <Nano/Managers/InputManager.h>
#include <Nano/Constants.h>

#include <Nano/Components/Components.h>

PlayerController::PlayerController() : _speed(350.0f), _jumpHeight(180.0f) {
}

void PlayerController::Update(float dt) {
	InputManager *input = InputManager::GetInstance();
	Transform *transform = _entity->GetTransform();
	Rigidbody *rigidbody = GetComponent<Rigidbody>();
	Vec2 vel = rigidbody->vel;
	vel.x = 0.0f;
	vel.x = _speed * input->GetAxis(IA_Horizontal);

	auto collided = GetComponent<Rigidbody>()->GetCollisionDirs();
	bool onGround = (collided & CD_Down) != 0;
	if (!onGround) {
		vel.y += kGravity * dt;
	}
	else {
		vel.y = 0.0f;
		if (input->IsDown(IT_Jump)) {
			vel.y = -sqrt(2.0f * _jumpHeight * kGravity);
			onGround = false;
			_isHoldingJump = true;
		}
	}
	if (_isHoldingJump && !input->IsHeld(IT_Jump)) {
		_isHoldingJump = false;
		if (vel.y < 0.0f) {
			vel.y *= 0.35f;
		}
	}
	rigidbody->vel = vel;

	Entity* text = _entity->GetEntitySystem()->FindEntity("PlayerPosText");
	if (text) {
		text->GetComponent<TextRenderer>()->SetText(transform->pos.ToString());
	}
}
