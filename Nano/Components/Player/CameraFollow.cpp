#include "CameraFollow.h"

#include <Nano/Constants.h>
#include <Nano/Components/Tilemap.h>

const static Vec2 kHalfScreen((float)kScreenWidth / 2.0f, (float)kScreenHeight / 2.0f);

void CameraFollow::Start() {
	_followTransform = GetEntitySystem()->FindEntity(_followName)->GetTransform();
	_boundsTilemap = GetEntitySystem()->FindEntity(_boundsName)->GetComponent<Tilemap>();
}

void CameraFollow::Update(float dt) {
	Transform *transform = GetTransform();
	Rect bounds = _boundsTilemap->GetBounds();
	transform->pos = _followTransform->pos - kHalfScreen;
	if (transform->pos.x > bounds.x + bounds.w - 1.5f * kScreenWidth) {
		transform->pos.x = bounds.x + bounds.w - kScreenWidth;
	}
	else {
		transform->pos.x = (float)(int)clamp(transform->pos.x, bounds.x, bounds.x + bounds.w - 2.0f * kScreenWidth);
	}
	transform->pos.y = (float)(int)clamp(transform->pos.y, bounds.y, bounds.y + bounds.h - kScreenHeight);
}

