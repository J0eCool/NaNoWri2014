#include "CameraFollow.h"

#include <Nano/Constants.h>

const static Vec2 kHalfScreen((float)kScreenWidth / 2.0f, (float)kScreenHeight / 2.0f);

void CameraFollow::Load(std::vector<std::string> const& args) {
	_followName = args[0];
}

void CameraFollow::Start() {
	_followTransform = GetEntitySystem()->FindEntity(_followName)->GetTransform();
}

void CameraFollow::Update(float dt) {
	Transform *transform = GetTransform();
	transform->pos = _followTransform->pos - kHalfScreen;
}

