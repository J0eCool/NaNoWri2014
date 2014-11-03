#include "Player.h"

#include "Transform.h"
#include "../Entity.h"
#include "../../Managers/InputManager.h"
#include "../../Util/Constants.h"
#include "../../Util/Math.h"

Player::Player() : _speed(350.0f), _jumpHeight(120.0f),
		_groundHeight(kScreenHeight - 100) {
}

void Player::Update(float dt) {
	InputManager *input = InputManager::GetInstance();
	Transform *transform = _entity->GetComponent<Transform>();
	_vel.x = 0.0f;
	_vel.x = _speed * input->GetAxis(IA_Horizontal);
	if (!onGround) {
		_vel.y += kGravity * dt;
		if (transform->pos.y + _vel.y * dt + transform->size.y > _groundHeight) {
			transform->pos.y = _groundHeight - transform->size.y;
			_vel.y = 0.0f;
			onGround = true;
		}
	}
	else {
		if (input->IsDown(IT_Jump)) {
			_vel.y = -sqrt(2.0f * _jumpHeight * kGravity);
			onGround = false;
		}
	}
	transform->pos += _vel * dt;
	transform->pos.x = clamp(transform->pos.x, 0, (float)kScreenWidth - transform->size.x);
}
