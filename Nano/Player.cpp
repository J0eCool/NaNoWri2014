#include "Player.h"

#include "Managers/InputManager.h"
#include "Util/Constants.h"
#include "Util/Math.h"

Player::Player(Vec2 size, Vec2 pos) : _size(size), _pos(pos),
		_speed(350.0f), _jumpHeight(120.0f), _groundHeight(kScreenHeight - 100) {
}

void Player::Update(float dt) {
	InputManager *input = InputManager::GetInstance();
	_vel.x = 0.0f;
	_vel.x = _speed * input->GetAxis(IA_Horizontal);
	if (!onGround) {
		_vel.y += kGravity * dt;
		if (_pos.y + _vel.y * dt + _size.y > _groundHeight) {
			_pos.y = _groundHeight - _size.y;
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
	_pos += _vel * dt;
	_pos.x = clamp(_pos.x, 0, (float)kScreenWidth - _size.x);
}

void Player::Draw(SDL_Renderer *renderer) const {
	SDL_Rect rect;
	rect.x = (int)_pos.x;
	rect.y = (int)_pos.y;
	rect.w = (int)_size.x;
	rect.h = (int)_size.y;

	SDL_SetRenderDrawColor(renderer, 0xff, 0x80, 0x80, 0xff);
	SDL_RenderFillRect(renderer, &rect);
}
