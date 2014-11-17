#include "CameraFollow.h"

#include <Nano/Constants.h>

const static Vec2 kHalfScreen((float)kScreenWidth / 2.0f, (float)kScreenHeight / 2.0f);

void CameraFollow::Start() {
	_followTransform = GetEntitySystem()->FindEntity(_followName)->GetTransform();
}

void CameraFollow::Update(float dt) {
	Transform *transform = GetTransform();
	transform->pos = _followTransform->pos - kHalfScreen;
	transform->pos.x = clamp(transform->pos.x, _leftBound, _rightBound - kScreenWidth);
	transform->pos.y = clamp(transform->pos.y, _upBound, _downBound - kScreenHeight);
}

