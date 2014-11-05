#include "Player.h"

#include "Transform.h"
#include "../Managers/InputManager.h"
#include "../Constants.h"

#include "Collider.h"
#include "Renderer.h"

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

	if (_entity->GetComponent<Collider>()->GetCollidedEntities().size() > 0) {
		_entity->GetComponent<Renderer>()->SetColor({ 0xff, 0x35, 0x38, 0xff });
	}
	else {
		_entity->GetComponent<Renderer>()->SetColor({ 0x20, 0xc0, 0xff, 0xff });
	}
}
