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
	vel.x = _speed * input->GetAxis(IA_Horizontal);
	if (sign(vel.x)) {
		_facingDir = sign(vel.x);
	}

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

	if (input->IsDown(IT_Shoot)) {
		Entity *bullet = new Entity("Bullet");
		bullet->AddComponent(CT_Collider, (new Collider())->SetArg("layerMask", "0x2"));
		bullet->AddComponent(CT_Bullet, new Bullet());
		bullet->AddComponent(CT_Renderer, (new Renderer())->SetArg("color", "0xd0,0xd0,0x20"));
		bullet->AddComponent(CT_Transform, (new Transform())->SetArg("size", "20,20"));
		bullet->GetTransform()->pos = transform->pos + transform->size / 2.0f + Vec2(_facingDir * transform->size.x / 2.0f + (_facingDir < 0 ? -20 : 0), -10.0f);
		bullet->GetComponent<Bullet>()->SetVel({ 600 * (float)_facingDir, 0 });
		GetEntitySystem()->AddEntity(bullet);
	}

	Entity* text = _entity->GetEntitySystem()->FindEntity("PlayerPosText");
	if (text) {
		text->GetComponent<TextRenderer>()->SetText(transform->pos.ToString());
	}
}
