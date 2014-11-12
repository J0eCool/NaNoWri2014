#include "Player.h"

#include <Nano/Managers/InputManager.h>
#include <Nano/Constants.h>

#include <Nano/Components/Components.h>

Player::Player() : _speed(350.0f), _jumpHeight(180.0f) {
}

void Player::Update(float dt) {
	InputManager *input = InputManager::GetInstance();
	Transform *transform = _entity->GetTransform();
	_vel.x = 0.0f;
	_vel.x = _speed * input->GetAxis(IA_Horizontal);

	auto collidedEntities = GetComponent<Collider>()->GetCollidedEntities();
	_onGround = collidedEntities.size() > 0 && _vel.y >= 0.0f;
	if (!_onGround) {
		_vel.y += kGravity * dt;
	}
	else {
		//transform->pos.y = collidedEntities[0]->GetTransform()->pos.y
		//	- transform->size.y;
		_vel.y = 0.0f;
		if (input->IsDown(IT_Jump)) {
			_vel.y = -sqrt(2.0f * _jumpHeight * kGravity);
			_onGround = false;
			_isHoldingJump = true;
		}
	}
	if (_isHoldingJump && !input->IsHeld(IT_Jump)) {
		_isHoldingJump = false;
		if (_vel.y < 0.0f) {
			_vel.y *= 0.35f;
		}
	}
	GetComponent<Rigidbody>()->vel = _vel;
	transform->pos.x = clamp(transform->pos.x, 0, (float)kScreenWidth - transform->size.x);

	Entity* text = _entity->GetEntitySystem()->FindEntity("PlayerPosText");
	if (text) {
		text->GetComponent<TextRenderer>()->SetText(transform->pos.ToString());
	}
}
